

#ifndef LAB6_RANGE_H
#define LAB6_RANGE_H

template <typename T> class Range {
public:
  T _start = 0, _end, _step = 1;

  class Iterator {
  private:
    T _current;
    T _step;
    T _end;

  public:
    T operator*() { return _current; }
    Iterator(T _current, T step, T end)
        : _current(_current), _step(step), _end(end) {}
    Iterator &operator++() {
      _current += _step;
      _current = _current < _end ? _current : _end;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp(*this);
      ++(*this);
      return tmp;
    }
    bool operator!=(const Iterator &other) {
      return _current != other._current;
    }
  };

  Range(T start, T end, T step) : _start(start), _end(end), _step(step) {}
  Range(T start, T end) : _start(start), _end(end) {}
  Range(T end) : _end(end) {}
  Iterator begin() { return Iterator(_start, _step, _end); }
  Iterator end() { return Iterator(_end, _step, _end); }
};

template <typename T> Range<T> make_range(T start, T end, T step = 1) {
  return Range<T>(start, end, step);
}

template <typename T> Range<T> make_range(T start, T end) {
  return Range<T>(start, end);
}

template <typename T> Range<T> make_range(T end) { return Range<T>(end); }

#endif // LAB6_RANGE_H
