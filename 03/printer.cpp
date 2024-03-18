#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

class Printer {
public:
  Printer(std::ostream &os, std::string prefix, std::string postfix)
      : _os(os), _prefix(prefix), _postfix(postfix) {}

  void operator()(const auto &x) { _os << _prefix << x << _postfix; };

private:
  std::ostream &_os;
  const std::string _prefix;
  const std::string _postfix;
};

int main() {
  /// Creates unary functor that takes one argument x (of any type)
  /// and outputs to given stream x surrounded by given prefix na postfix
  /// e.g. in the following  [ x ]
  /// Hint: define function template.
  Printer printer(std::cout, "[ ", " ] ");
  printer("hello"); // [ hello ]
  std::cout << "\nv = ";
  std::vector<int> v = {1, 2, 3, 4};
  std::for_each(v.begin(), v.end(), printer); // v = [ 1 ] [ 2 ] [ 3 ] [ 4 ]
  std::cout << std::endl;

  std::ofstream file("myFile.txt");
  Printer filePrinter(file, "- ", "\n");
  filePrinter(5);
  filePrinter("My text");
  return 0;
}
/** myFile.txt
- 5
- My text
*/