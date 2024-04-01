
#include "staticVector.h"
#include <iomanip>
#include <iostream>

using namespace std;
#define LOG(x) std::cout << #x << " = " << (x) << std::endl

int main() {
  cout << fixed << setprecision(2);
  using DWector = Vector<double, 4>;

  DWector m0{}; // Vector filled with zeroes.
  LOG(m0);

  DWector m1{1., 2., 3., 4.}; // Vector from initialization_list
  LOG(m1);

  const DWector m2 = m1; // copy constructor
  m1[2] = -5;
  m1[3] = -20;
  LOG(m1);

  DWector::value_type element = m2[2];
  LOG(element);
  LOG(m2.size());

  DWector m3 = m1 + m2; // vector sum
  LOG(m3);

  Vector<double, 3> m4{5.0, 6.2, 1.34};
  // auto mm = m3 + m4; // compilation ERROR

  return 0;
}
/** Expected output:
m0 = 0.00 0.00 0.00 0.00
m1 = 1.00 2.00 3.00 4.00
m1 = 1.00 2.00 -5.00 -20.00
element = 3.00
m2.size() = 4
m3 = 2.00 4.00 -2.00 -16.00
*/
