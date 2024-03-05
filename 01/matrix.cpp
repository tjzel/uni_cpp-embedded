#include "matrix.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <sstream>

Matrix::Matrix() { std::cout << "Default constructor" << std::endl; }

Matrix::Matrix(const size_t N, const size_t M) : N(N), M(M) {
  std::cout << "Matrix size constructor" << std::endl;
  data = new double[N * M];
  std::fill(data, data + N * M, 0.0);
}

Matrix::Matrix(
    const std::initializer_list<const std::initializer_list<double>> &list) {
  std::cout << "Matrix initializer constructor" << std::endl;
  size_t m = 0;
  for (const auto &row : list) {
    m = std::max(m, row.size());
  }
  N = list.size();
  M = m;
  data = new double[N * M];
  auto current = data;
  for (const auto &row : list) {
    auto last = std::copy(row.begin(), row.end(), current);
    std::fill(last, current + M, 0.0);
    current += M;
  }
}

Matrix::Matrix(Matrix &&matrix) {
  std::cout << "Matrix move constructor" << std::endl;
  N = std::exchange(matrix.N, 0);
  M = std::exchange(matrix.M, 0);
  data = std::exchange(matrix.data, nullptr);
}

Matrix &Matrix::operator=(Matrix &&matrix) {
  if (this == &matrix) {
    return *this;
  }
  std::cout << "Matrix move assignment" << std::endl;
  N = std::exchange(matrix.N, 0);
  M = std::exchange(matrix.M, 0);

  delete[] data;
  data = std::exchange(matrix.data, nullptr);

  return (*this);
}

Matrix::Matrix(const Matrix &matrix) : N(matrix.N), M(matrix.M) {
  std::cout << "Matrix copy constructor" << std::endl;
  data = new double[N * M];
  std::copy(matrix.data, matrix.data + N * M, data);
}

double Matrix::operator()(size_t row, size_t col) const {
  return data[(row - 1) * M + (col - 1)];
}

Matrix Matrix::operator-() const {
  std::cout << "Unary minus" << std::endl;

  auto matrix = Matrix(N, M);
  for (size_t row = 1; row <= N; row++) {
    for (size_t col = 1; col <= M; col++) {
      matrix.data[(row - 1) * M + (col - 1)] = -((*this)(row, col));
    }
  }
  return matrix;
}

std::string Matrix::toString() const {
  if (data == nullptr) {
    return "Data is empty\n";
  }
  std::stringstream ss;
  for (size_t row = 1; row <= N; row++) {
    for (size_t col = 1; col <= M; col++) {
      ss << (*this)(row, col) << ' ';
    }
    ss << '\n';
  }
  return ss.str();
}

Matrix::~Matrix() {
  std::cout << "Matrix destructor" << std::endl;
  delete[] data;
}

std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
  out << matrix.toString();
  return out;
}

MatrixWithLabel::MatrixWithLabel(const std::string &label, const size_t N,
                                 const size_t M)
    : Matrix(N, M), label(label) {
  std::cout << "MatrixWithLabel size constructor" << std::endl;
};

MatrixWithLabel::MatrixWithLabel(
    const std::string &label,
    const std::initializer_list<const std::initializer_list<double>> list)
    : Matrix(list), label(label) {
  std::cout << "MatrixWithLabel initializer constructor" << std::endl;
};

MatrixWithLabel::MatrixWithLabel(const MatrixWithLabel &matrix)
    : Matrix(matrix), label(matrix.label) {
  std::cout << "MatrixWithLabel copy constructor" << std::endl;
};

MatrixWithLabel &MatrixWithLabel::operator=(MatrixWithLabel &&matrix) {
  std::cout << "MatrixWithLabel move assignment" << std::endl;

  label = std::exchange(matrix.label, "");
  Matrix::operator=(std::move(matrix));

  return (*this);
}

std::string MatrixWithLabel::getLabel() { return label; }

void MatrixWithLabel::setLabel(const std::string &newLabel) {
  label = newLabel;
}
