#include "StaticContainer2.h"
#include <iostream>
using namespace std;
int main() {
  Box::verbose = true;
  // Container::verbose = true;

  Container p1(10);
  Container p2(10);
  Container p3 = p1 + p2;

  // The following lines should not compile
  // Container copy(p2); // ERROR!!!
  // p3 = p1;            // ERROR!!!

  cout << p1 << p2 << p3 << endl;

  cout << "== Move semantics \n"; // No copy after this line
  p1 = p2 + p3;
  Container p4 = std::move(p2);

  cout << p1 << p3 << p4 << endl;
  // cout << p2 << endl; // p2 should not be used here!!!
  cout << "== Cleaning up!\n";
  return 0;
}
/** Expected output:
 Box[1] constructor with content = 10
 Box[2] constructor with content = 10
 Box[3] constructor with content = 20
 [10]  [10]  [20]
== Move semantics
 Box[4] constructor with content = 30
 Box[1] move assignment, swapping content with Box[4]
 Box[4] destructor
 Box[5] move constructor from Box[2]
 [30]  [20]  [10]
== Cleaning up!
 Box[5] destructor
 Box[3] destructor
 Box[2] destructor
 Box[1] destructor
 */