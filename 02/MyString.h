
#ifndef LAB2_MYSTRING_H
#define LAB2_MYSTRING_H

#include <iostream>

namespace emcpp{

    class MyString : public std::string{
        using Base = std::string;
        static void logger(const std::string & str ) {
            if (logging) std::cout << str << std::endl;
        }
    public:
        static bool logging;
        MyString() : Base(){
            logger("Default constructor");
        }
        MyString(const char * c) : Base(c){
            logger("Constructor from C string");
        }
        MyString(const MyString & s) : Base(s){
            logger("Copy constructor");
        }
        MyString(MyString && s) : Base(std::move(s)){
            logger("Move constructor");
        }
        MyString & operator=(const MyString & s){
            Base::operator=(s);
            logger("Copy assign operator");
            return * this;
        }
        MyString & operator=(MyString && s){
            Base::operator=(std::move(s));
            logger("Move assign operator");
            return *this;
        }
    };
    bool MyString::logging = true;

} // end of namespace emcpp

#endif //LAB2_MYSTRING_H
