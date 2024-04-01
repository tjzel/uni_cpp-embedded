
#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H

#include "vector.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

template <typename T, size_t N> class Vector : public IVector<T, N> {
public:
  size_t length = N;
  friend class Vector<T, 0>;

private:
  T data[N];

  Vector(T parameter) { std::fill(data, data + N, parameter); }

public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef T *pointer;
  typedef T &reference;
  typedef const T &const_reference;

  Vector() { std::fill(data, data + N, 0); }

  Vector(const Vector &v) { std::copy(v.data, v.data + N, data); }

  explicit operator Vector<T, 0>() {
    Vector<T, 0> result(N);
    for (size_t i = 0; i < N; i++) {
      result[i] = data[i];
    }
    return result;
  }

  template <typename S, size_t M> explicit operator Vector<S, M>() {
    Vector<S, M> result;
    for (size_t i; i < M && i < N; i++) {
      result[i] = (S)data[i];
    }
  }

  Vector &operator=(const Vector &m) {
    for (size_t i = 0; i < N; i++) {
      data[i] = m.data[i];
    }
  }

  Vector(const std::initializer_list<T> &list) {
    std::copy(list.begin(), list.end(), data);
  }

  friend Vector operator+(const Vector &u, const Vector &v) {
    Vector<T, N> result;
    for (size_t i = 0; i < N && i < v.length; i++) {
      result[i] = u[i] + v[i];
    }
    return result;
  }

  friend Vector operator+(const Vector<T, N> &u, const Vector<T, 0> &v) {
    if (N != v.length) {
      throw VectorException();
    }
    Vector<T, N> result;
    for (size_t i = 0; i < N && i < v.length; i++) {
      result[i] = u[i] + v[i];
    }
    return result;
  }

  friend Vector operator+(const Vector<T, 0> &u, const Vector &v) {
    if (N != u.length) {
      throw VectorException();
    }
    Vector<T, N> result;
    for (size_t i = 0; i < N && i < u.length; i++) {
      result[i] = u[i] + v[i];
    }
    return result;
  }

  // friend Vector<T, N> operator+(const Vector<T, N> &u, const Vector<T, 0> &v)
  // {
  //   if (M != 0 && M != N) {
  //     throw VectorException();
  //   }
  //   if (M == 0) {
  //     Vector<T, N> result;
  //     for (size_t i = 0; i < N && i < v.length; i++) {
  //       result[i] = u[i] + v[i];
  //     }
  //     return result;
  //   } else {
  //     Vector<T, N> result;
  //     for (size_t i = 0; i < N; i++) {
  //       if (i < v.length) {
  //         result[i] = u[i] + v[i];
  //       } else {
  //         result[i] = u[i];
  //       }
  //     }
  //     return result;
  //   }
  // }

  constexpr size_type size() const { return N; }

  const_reference get(size_type index) const { return data[index]; }

  void set(size_type index, const_reference value) { data[index] = value; }

  reference operator[](size_type index) { return data[index]; }
  const_reference operator[](size_type index) const { return data[index]; }

  friend std::ostream &operator<<(std::ostream &out, const Vector &v) {
    for (auto elem : v.data) {
      out << elem << " ";
    }
    return out;
  }
};

#endif // STATIC_VECTOR_H
