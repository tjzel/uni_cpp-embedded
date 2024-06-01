
#include <array>
#include <cmath>
#include <iostream>

/**
 * Exercise 2a:
 * Implement function power that computes x^n
 * during compilation using recurrent formula
   x^2n = (x^n)^2
   x^2n+1 = (x^2n)*x
  */
consteval auto power(auto x, int n) {
  if (n == 0) {
    return 1;
  } else if (n % 2 == 0) {
    return power(x, n / 2) * power(x, n / 2);
  } else {
    return x * power(x, n - 1);
  }
}

constinit double fiveToPowerFour = power(5, 4);

/**
 *  Exercise 2b:
 * Implement function generate_triangle that during compilation
 * generates the Pascal triangle of the given size N.
 * Pascal triangle
 * https://en.wikipedia.org/wiki/Pascal%27s_triangle
 *
 */
template <size_t N>
constexpr std::array<int, (N + 1) * N / 2> generate_triangle() {
  std::array<int, (N + 1) * N / 2> triangle{};
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j <= i; j++) {
      if (j == 0 || j == i) {
        triangle[(i * (i + 1) / 2) + j] = 1;
      } else {
        triangle[(i * (i + 1) / 2) + j] = triangle[((i - 1) * i) / 2 + j - 1] +
                                          triangle[((i - 1) * i) / 2 + j];
      }
    }
  }
  return triangle;
}

template <size_t N> class PascalTriangle {

  static constexpr const std::array<int, (N + 1) * N / 2> triangle =
      generate_triangle<N>();

public:
  constexpr int operator()(size_t n, size_t m) const {
    return triangle[(n * (n + 1) / 2) + m];
  }
};

template <auto N> consteval PascalTriangle<N> generatePascalTriangle() {
  return PascalTriangle<N>();
}

constexpr size_t n = 10;
constexpr auto triangle = generatePascalTriangle<n>();

int main() {

  static_assert(triangle(0, 0) == 1);
  static_assert(triangle(5, 3) == 10);
  static_assert(triangle(9, 4) == 126);
}