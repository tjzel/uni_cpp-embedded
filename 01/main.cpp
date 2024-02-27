#include "matrix.h"
#include <iostream>

int main(void) {

  std::cout << "Initialization" << std::endl;
  Matrix m1;
  std::cout << m1 << std::endl;

  Matrix m2(3, 4);
  std::cout << m2 << std::endl;

  Matrix m3({{1, 2, 3}, {32, 23, 22}, {3, 234, 23, 44}});
  std::cout << m3 << std::endl;

  std::cout << "Move" << std::endl;
  Matrix m4 = std::move(m2);
  std::cout << m4 << std::endl;
  std::cout << m2 << std::endl;

  Matrix m5 = -m4;
  std::cout << m5 << std::endl;

  m2 = std::move(m3);
  std::cout << m2 << std::endl;

  Matrix *pm = new Matrix(-m2);
  std::cout << (*pm)(2, 1) << std::endl;

  std::cout << "Inheritance" << std::endl;
  MatrixWithLabel l0("B", 3, 4);
  MatrixWithLabel l1({{1, 2}, {4, 5}});
  l1.setLabel("A");
  std::cout << l1.getLabel() << std::endl;
  std::cout << l1 << std::endl;
  MatrixWithLabel l2 = l1;
  std::cout << "Inter" << std::endl;
  MatrixWithLabel l3 = std::move(l1);
  std::cout << l1.getLabel() << " " << l2.getLabel() << " " << l3.getLabel()
            << std::endl;
  l2 = std::move(l3);
  std::cout << l2 << std::endl;

  return 0;
}