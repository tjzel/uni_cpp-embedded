
#include "staticVector.h"

template <typename T> class Vector<T, 0> : public IVector<T, 0> {
public:
  size_t length;

private:
  std::unique_ptr<T[]> data;

public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef T *pointer;
  typedef T &reference;
  typedef const T &const_reference;

  Vector(size_t length) : length(length), data(std::make_unique<T[]>(length)) {}

  Vector(const std::initializer_list<T> &list)
      : length(list.size()), data(std::make_unique<T[]>(list.size())) {
    std::copy(list.begin(), list.end(), data.get());
  }

  Vector(const Vector &v)
      : length(v.length), data(std::make_unique<T[]>(length)) {
    std::copy(v.data.get(), v.data.get() + length, data.get());
  }
  Vector &operator=(const Vector &m) {
    std::copy(m.data, m.data + length, data);
  }

  Vector(Vector &&v) : length(v.length), data(v.data.release()) {}

  Vector &operator=(const Vector &&m) {
    length = m.length;
    data = m.data.swap(data);
  }

  friend Vector operator+(const Vector &u, const Vector &v) {
    if (u.length != v.length) {
      throw VectorException();
    }
    Vector<T, 0> result(u.length);
    for (size_t i = 0; i < u.length; i++) {
      result[i] = u[i] + v[i];
    }
    return result;
  }

  template <size_t N> explicit operator Vector<T, N>() {
    if (N == 0) {
      return Vector<T, N>(*this);
    }
    Vector<T, N> result;
    for (size_t i = 0; i < N && i < length; i++) {
      result[i] = data[i];
    }
    return result;
  }

  void resize(size_t newLength) {
    auto newData = std::make_unique<T[]>(newLength);
    std::copy(data.get(), data.get() + newLength, newData.get());
    if (newLength < length) {
      std::fill(newData.get() + newLength, newData.get() + length, 0);
    }
    newData.swap(data);
    length = newLength;
  }

  constexpr size_type size() const { return length; }

  const_reference get(size_type index) const { return data[index]; }

  void set(size_type index, const_reference value) { data[index] = value; }

  reference operator[](size_type index) { return data[index]; }
  const_reference operator[](size_type index) const { return data[index]; }

  friend std::ostream &operator<<(std::ostream &out, const Vector &v) {
    // for (auto elem : v.data) {
    // out << elem << " ";
    // }
    for (size_t i = 0; i < v.length; i++) {
      out << v[i] << " ";
    }
    return out;
  }
};
