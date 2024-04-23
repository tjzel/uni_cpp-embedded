
#ifndef LAB8_VECTOR_H
#define LAB8_VECTOR_H

#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

template <typename T, size_t N, template <typename, size_t> class Policy>
class Vector;

template <typename T> class vector_traits {
public:
  typedef const T &&GetSetType;
  typedef T ScalarType;

  static GetSetType mult(ScalarType scalar, GetSetType value) {
    return scalar * value;
  }
  static T defaultValue() { return 0; }
};

template <> class vector_traits<int> {
public:
  typedef int GetSetType;
  typedef int ScalarType;

  static GetSetType mult(ScalarType scalar, GetSetType value) {
    return scalar * value;
  }
  static int defaultValue() { return 0; }
};

template <> class vector_traits<double> {
public:
  typedef double GetSetType;
  typedef double ScalarType;

  static GetSetType mult(ScalarType scalar, GetSetType value) {
    return scalar * value;
  }
  static double defaultValue() { return 0; }
};

template <> class vector_traits<std::string> {
public:
  typedef const std::string GetSetType;
  typedef int ScalarType;

  static GetSetType mult(ScalarType scalar, GetSetType value) {
    std::string out;
    for (int i = 0; i < scalar; i++) {
      out += value;
    }
    return out;
  }
  static std::string defaultValue() { return "0"; }
};

template <typename T, size_t N> class IInitPolicy {
public:
  virtual void init(T (&data)[N]) = 0;
};

template <size_t N> class ICheckPolicy {
public:
  virtual void checkIndex(size_t index) const = 0;
};

template <typename T, size_t N> class NoInitPolicy : public IInitPolicy<T, N> {
public:
  void init(T (&data)[N]) {}
};

template <typename T, size_t N>
class ZeroInitPolicy : public IInitPolicy<T, N> {
public:
  void init(T (&data)[N]) {
    for (size_t i = 0; i < N; i++) {
      data[i] = vector_traits<T>::defaultValue();
    }
  }
};

template <size_t N> class NoCheckPolicy : public ICheckPolicy<N> {
public:
  void checkIndex(size_t index) const {};
};

template <size_t N> class StrictCheckPolicy : public ICheckPolicy<N> {
public:
  void checkIndex(size_t index) const {
    if (index >= N) {
      throw std::runtime_error("Index out of bounds.");
    }
  };
};

template <typename T, size_t N, class InitPolicy, class CheckPolicy>
class IVectorPolicy : public InitPolicy, public CheckPolicy {};

template <typename T, size_t N>
class FastPolicy : public NoInitPolicy<T, N>, public NoCheckPolicy<N> {};

template <typename T, size_t N>
class SafePolicy : public ZeroInitPolicy<T, N>, public StrictCheckPolicy<N> {};

template <typename T, size_t N>
class InitFastPolicy : public ZeroInitPolicy<T, N>, public NoCheckPolicy<N> {};

template <typename T, size_t N, template <typename, size_t> class Policy>
class Vector : public Policy<T, N> {
  T data[N];

public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef T *pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef vector_traits<T>::GetSetType GetSetType;
  typedef vector_traits<T>::ScalarType ScalarType;

  Vector() { this->Policy<T, N>::init(data); }
  Vector(const Vector &v) = default;
  Vector &operator=(const Vector &m) = default;

  Vector(const std::initializer_list<T> &list) {
    std::copy(list.begin(), list.end(), data);
  }
  size_type size() const { return N; }

  GetSetType get(size_type index) const {
    this->Policy<T, N>::checkIndex(index);
    return data[index];
  }

  void set(size_type index, GetSetType value) {
    this->Policy<T, N>::checkIndex(index);
    data[index] = value;
  }

  friend Vector operator*(ScalarType x, const Vector &v) {
    Vector result;
    for (int i = 0; i < v.size(); ++i) {
      result.set(i, vector_traits<T>::mult(x, v.get(i)));
    }
    return result;
  }

  friend std::ostream &operator<<(std::ostream &out, const Vector &v) {
    for (int i = 0; i < v.size(); ++i) {
      out << v.get(i) << " ";
    }
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Vector &v) {
    Vector::value_type value;
    for (int i = 0; i < v.size(); ++i) {
      in >> value;
      if (in)
        v.set(i, value);
    }
    return in;
  }
};

#endif // LAB8_VECTOR_H