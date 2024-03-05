#include "MyString.h"
#include <algorithm>
#include <iostream>
using namespace std;

class String {
  using string = emcpp::MyString;
  //   using string = std::string;

  /// Store a pointer to dynamically allocated string!

  std::shared_ptr<string> str_ptr;

public:
  String() : str_ptr(make_shared<string>()){}; /// creates an empty string

  String(const char *str)
      : str_ptr(make_shared<string>(str)){}; /// copy C-string

  String(const String &str) : str_ptr(str.str_ptr){}; /// no copy

  String operator=(const String &s) {
    if (this == &s) {
      return *this;
    }
    str_ptr = s.str_ptr;
    return *this;
  }; /// no copy

  /// makes a copy of a string if it has more than one reference.
  void set(int index, char ch) {
    if (str_ptr.use_count() > 1) {
      str_ptr = std::make_shared<string>(*str_ptr);
    }
    str_ptr->assign(index, ch);
  }

  /// no copy
  char get(int index) const { return str_ptr->at(index); }

  /// creates a new string only if both strings are non empty
  friend String operator+(String a, String b) {
    if (a.str_ptr->empty()) {
      return b;
    }
    if (b.str_ptr->empty()) {
      return a;
    }

    return String((*a.str_ptr + *b.str_ptr).c_str());
  };
  friend std::ostream &operator<<(std::ostream &out, String s) {
    out << *s.str_ptr;
    return out;
  };
};
