#pragma once

#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

template <typename T, size_t N, size_t M> class Matrix {

  T data[N * M];

public:
  constexpr size_t numberOfRows() const { return N; }
  constexpr size_t numberOfColumns() const { return M; }

  Matrix(int nrows = N, int ncols = M) { std::fill_n(data, N * M, T{}); }
  Matrix(const std::initializer_list<std::initializer_list<T>> &list) {
    T *p = data;
    for (const auto &row : list) {
      T *p2 = std::copy(row.begin(), row.end(), p);
      std::fill(p2, p += M, T{});
    }
  }

  Matrix(const Matrix &m) { std::copy_n(m.data, N * M, data); }

  Matrix &operator=(const Matrix &m) {
    if (&m != this) {
      std::copy_n(m.data, N * M, data);
    }
    return *this;
  }

  const T &operator()(int i, int j) const { return data[(i - 1) * M + j - 1]; }

  T &operator()(int i, int j) { return data[(i - 1) * M + j - 1]; }

  friend Matrix operator+(const Matrix &a, const Matrix &b) {
    Matrix r;
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= M; ++j) {
        r(i, j) = a(i, j) + b(i, j);
      }
    }
    return r;
  }

  class Iterator {
    int i_, j_;
    const Matrix &matrix_;

  public:
    Iterator(int i, int j, const Matrix<T, N, M> &matrix)
        : i_(i), j_(j), matrix_(matrix) {}
    Iterator &operator++() {
      ++j_;
      if (j_ > M) {
        j_ = 1;
        ++i_;
      }
      return *this;
    }
    bool operator!=(const Iterator &other) const {
      return i_ != other.i_ || j_ != other.j_;
    }
    const T &operator*() { return matrix_(i_, j_); }

    const T *operator->() const {
      return matrix_.data + (j_ - 1) + (i_ - 1) * M;
    }
  };

  Iterator begin() const { return Iterator(1, 1, *this); }
  Iterator end() const { return Iterator(N + 1, 1, *this); }

  class RowIterator {
    const int i_;
    int j_;
    const Matrix<T, N, M> &matrix_;

  public:
    RowIterator(int i, int j, const Matrix<T, N, M> &matrix)
        : i_(i), j_(j), matrix_(matrix) {}
    RowIterator &operator++() {
      ++j_;
      return *this;
    }
    bool operator!=(const RowIterator &other) const {
      return i_ != other.i_ || j_ != other.j_;
    }
    const T &operator*() { return matrix_(i_, j_); }

    const T *operator->() const {
      return matrix_.data + (j_ - 1) + (i_ - 1) * M;
    }
  };

  RowIterator row_begin(int i) const { return RowIterator(i, 1, *this); }
  RowIterator row_end(int i) const { return RowIterator(i, M + 1, *this); }

  class ColumnIterator {
    int i_;
    const int j_;
    const Matrix<T, N, M> &matrix_;

  public:
    ColumnIterator(int i, int j, const Matrix<T, N, M> &matrix)
        : i_(i), j_(j), matrix_(matrix) {}
    ColumnIterator &operator++() {
      ++i_;
      return *this;
    }
    bool operator!=(const ColumnIterator &other) const {
      return i_ != other.i_ || j_ != other.j_;
    }
    const T &operator*() { return matrix_(i_, j_); }

    const T *operator->() const {
      return matrix_.data + (j_ - 1) + (i_ - 1) * M;
    }
  };

  ColumnIterator col_begin(int j) const { return ColumnIterator(1, j, *this); }
  ColumnIterator col_end(int j) const {
    return ColumnIterator(N + 1, j, *this);
  }

  typedef ColumnIterator col_iterator;
};

template <typename T, size_t N, size_t M>
void printMatrix(const Matrix<T, N, M> &m, int width = 10) {
  for (int i = 1; i <= m.numberOfRows(); ++i) {
    for (int j = 1; j <= m.numberOfColumns(); ++j) {
      if (j != 1)
        cout << " ";
      cout << setw(width) << m(i, j);
    }
    cout << endl;
  }
}
