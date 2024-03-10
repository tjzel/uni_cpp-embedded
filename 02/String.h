#include "MyString.h"
#include <algorithm>
#include <iostream>
#include <memory>

class String {
  using string = emcpp::MyString;
  //   using string = std::string;

  std::shared_ptr<string> str_ptr;

public:
  String() : str_ptr(std::make_shared<string>()){};

  String(const char *str) : str_ptr(std::make_shared<string>(str)){};

  String(const String &str) : str_ptr(str.str_ptr){};

  String operator=(const String &s) {
    if (this == &s) {
      return *this;
    }
    str_ptr = s.str_ptr;
    return *this;
  };

  void set(int index, char ch) {
    if (str_ptr.use_count() > 1) {
      str_ptr = std::make_shared<string>(*str_ptr);
    }
    (*str_ptr)[index] = ch;
  }

  char get(int index) const { return str_ptr->at(index); }

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
