
#ifndef LAB6_FILTER_H
#define LAB6_FILTER_H
#include <iostream>
#include <iterator>

template <typename Container, typename Predicate> class ForwardIterator {
public:
  typedef ForwardIterator const_iterator;
  typedef typename Container::value_type value_type;
  typedef typename Container::const_iterator inner_iterator;

private:
  const Container &c_;
  const Predicate &p_;
  inner_iterator it_;

public:
  ForwardIterator(const Container &c, const Predicate &p)
      : c_(c), p_(p), it_(c.begin()) {
    advance();
  }

  ForwardIterator(const Container &c, const Predicate &p, inner_iterator it)
      : c_(c), p_(p), it_(it) {
    advance();
  }

  ForwardIterator &operator++() {
    ++it_;
    advance();
    return *this;
  }

  inline void advance() {
    while (it_ != c_.end() && !p_(*it_)) {
      ++it_;
    }
  }

  bool operator!=(const ForwardIterator &other) const {
    return it_ != other.it_;
  }

  const auto &operator*() const { return *it_; }

  const auto *operator->() const { return &*it_; }

  ForwardIterator begin() const { return ForwardIterator(c_, p_); }

  ForwardIterator end() const { return ForwardIterator(c_, p_, c_.end()); }
};

template <typename Container, typename Predicate>
ForwardIterator<Container, Predicate> make_filter(const Container &c,
                                                  const Predicate &p) {
  return ForwardIterator<Container, Predicate>(c, p);
};

#endif // LAB6_FILTER_H
