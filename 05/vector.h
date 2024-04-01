#pragma once

#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

template <typename T, size_t N> class IVector {
public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef T *pointer;
  typedef T &reference;
  typedef const T &const_reference;

  virtual constexpr size_type size() const = 0;
  virtual const_reference get(size_type index) const = 0;
  virtual void set(size_type index, const_reference value) = 0;
  virtual reference operator[](size_type index) = 0;
  virtual const_reference operator[](size_type index) const = 0;
  virtual void resize(size_t size){};
};

class VectorException : std::runtime_error {
public:
  VectorException() : std::runtime_error("Vector's lengths don't match.") {}
};

template <typename T, size_t N> class Vector;

template <typename T> class Vector<T, 0>;
