#include <cmath>
#include <iostream>

/// Computes n-th root of x
double sqrtn(int n, double x) { return exp(log(x) / n); }
double power(double x, double y) { return exp(log(x) * y); }
template <typename F, typename G>
double function(int n, double y, double z, F f, G g) {
  return (f(n, y) > z) ? g(z, y) : g(y, z);
}

int main() {
  double (*sqrtnPtr)(int, double) = sqrtn;
  double (*powerPtr)(double, double) = power;
  double (*functionPtr)(int, double, double, double (*)(int, double),
                        double (*)(double, double)) = function;
  std::cout << functionPtr(2, 10, 3, sqrtnPtr, powerPtr) << std::endl;
  std::cout << functionPtr(3, 10, 3, sqrtnPtr, powerPtr) << std::endl;
  return 0;
}
