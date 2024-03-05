

#ifndef LAB2__BOX_H_
#define LAB2__BOX_H_

#include <iostream>

class Box{
  int id;
  int content = 0;
  static int lastID;
 public:
  static bool verbose;
  Box() : id(++lastID) {
	if(verbose) std::cout << " Box[" << id << "] default constructor" << std::endl;
  }
  Box(int content) : id(++lastID), content(content){
	if(verbose) std::cout << " Box[" << id << "] constructor with content = " << content << std::endl;
  }
  Box(const Box & box) : id(++lastID), content(box.content) {
	if (verbose) std::cout << " Box[" << id << "] copy constructor from Box[" << box.id << "]"<< std::endl;
  }
  Box & operator= (const Box & box){
	if (verbose) std::cout << " Box[" << id << "] copy assignment from Box[" << box.id << "]"<< std::endl;
	content = box.content;
	return *this;
  }
  Box(Box && box) : id(++lastID), content(box.content) {
	if (verbose) std::cout << " Box[" << id << "] move constructor from Box["<< box.id << "]" << std::endl;
	box.content=0;
  }
  Box & operator= (Box && box){
	if (verbose) std::cout << " Box[" << id << "] move assignment, swapping content with Box[" << box.id << "]"<< std::endl;
	std::swap(content,box.content);
	return *this;
  }

  ~Box(){
	if (verbose) std::cout << " Box[" << id << "] destructor "<< std::endl;
  }
  void setContent(int content){
	this->content = content;
  }
  int getContent() const {
	return content;
  }
};

int Box::lastID = 0;
bool Box::verbose = false;

#endif //LAB2__BOX_H_