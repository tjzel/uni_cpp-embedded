
// Compilation:
//   g++ ex_11_2_Mandelbrot.cpp EasyBMP.cpp -O2 -std=c++14 -o mandelbrot

#include "EasyBMP.h"
#include <chrono>
#include <complex>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;
typedef complex<double> Complex;
/**
 * Returns functional object that converts pixel position to point in the
 * complex plane.
 * @param imageWidth   image width
 * @param imageHeight  image hight
 * @param x1           minimal x
 * @param y1           minimal y
 * @param x2           maximal x
 * @param y2           maximal y
 * @return             functional object
 */
auto scaleFromPixelToComplex(int imageWidth, int imageHeight, double x1,
                             double y1, double x2, double y2) {
  double sx = (x2 - x1) / imageWidth;
  double sy = (y2 - y1) / imageHeight;
  return [=](int x, int y) { return Complex(x1 + sx * x, y2 - sy * y); };
}

/**
 * Checks if given complex number c is in not the Mandelbrot set.
 * @param c complex number
 * @param maxNumberOfIterations  maximal number of iterations
 * @param escapeThreshold
 * @return number of iterations after which image of 0 has module greather
 *         than escapeTreshold or 0 is maxNumberOfIteration was reached.
 */
static auto MandelbrotSetIterations(Complex c, size_t maxNumberOfIterations,
                                    double escapeThreshold = 4.0) {
  Complex x = 0;
  for (int i = 0; i < maxNumberOfIterations; i++) {
    x = x * x + c;
    if (abs(x) > escapeThreshold)
      return i + 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {

  const int imageWidth = 1000;             // bitmap width
  const int imageHeight = 1000;            // bitmap height
  const char *fileName = "mandelbrot.bmp"; // file name to output bitmap

  double x1 = -2, x2 = 1, // Rectangle in the complex plane [x1, x2]x[y1,,y2]
      y1 = -1, y2 = 1;    // that will plotted on bitmap.

  size_t maxNumberOfIteration = 2000;
  double escapeThreshold = 4;

  BMP Output;                              // We create bitmap
  Output.SetSize(imageWidth, imageHeight); // We set bitmap sizes
  Output.SetBitDepth(24);                  // We set color depth
  // Each pixel has 24 bits (8 bits for each RGB component)

  auto pixelToComplex =
      scaleFromPixelToComplex(imageWidth, imageHeight, x1, y1, x2, y2);

  auto iterationsToPixel = [](size_t numerOfIterations) {
    RGBApixel pixel;
    pixel.Blue = 0;
    pixel.Green = (ebmpBYTE)0;
    pixel.Red = (ebmpBYTE)0;
    if (numerOfIterations > 0) {
      pixel.Green = (ebmpBYTE)255 - 10 * (numerOfIterations % 20);
      pixel.Red = (ebmpBYTE)255 - 10 * (numerOfIterations % 10);
    }
    pixel.Alpha = 0;
    return pixel;
  };

  auto start = std::chrono::steady_clock::now();

  constexpr int numberOfExtraThreads = 12;
  std::vector<std::thread> threads;
  std::mutex columnMutex;
  int column = 0;

  auto getColumn = [&]() {
    std::lock_guard<std::mutex> lock(columnMutex);
    return column++;
  };

  auto threadFunction = [&]() {
    for (unsigned y = getColumn(); y < imageHeight; y = getColumn()) {
      for (unsigned x = 0; x < imageWidth; x++) {

        Complex c = pixelToComplex(x, y);

        auto numberOfIteration =
            MandelbrotSetIterations(c, maxNumberOfIteration, escapeThreshold);
        auto pixel = iterationsToPixel(numberOfIteration);
        Output.SetPixel(x, y, pixel);
      }
    }
  };

  for (size_t i = 0; i < numberOfExtraThreads; i++) {
    threads.emplace_back(std::thread(threadFunction));
  }

  threadFunction();

  for (auto &thread : threads) {
    thread.join();
  }

  auto stop = std::chrono::steady_clock::now();
  std::cout << "Time used : "
            << std::chrono::duration_cast<std::chrono::milliseconds>(stop -
                                                                     start)
                   .count()
            << " ms." << endl;
  std::cout << "Bitmap written to " << fileName << "." << endl;
  Output.WriteToFile(fileName);
  return 0;
}
