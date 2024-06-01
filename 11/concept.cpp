#include <iostream>
#include <vector>

template <typename T>
concept Container = requires(T t) {
  typename T::iterator;
  typename T::value_type;
  { t.begin() } -> std::same_as<typename T::iterator>;
  { t.end() } -> std::same_as<typename T::iterator>;
  { *t.begin() + *t.begin() };
};

template <typename T>
concept hasOstreamOperator = requires(T t) {
  { std::cout << t } -> std::same_as<std::ostream &>;
};

template <typename T>
concept hasPrintMethod = requires(T t) {
  { t.print() } -> std::same_as<void>;
};

template <typename T>
concept Printable = hasOstreamOperator<T> || hasPrintMethod<T>;

template <typename T>
void print(const T &t)
  requires Printable<T>
{
  if constexpr (hasOstreamOperator<T>) {
    std::cout << t << " ";
  } else {
    t.print();
    std::cout << " ";
  }
}

template <typename T>
void print(const T &t)
  requires Container<T> && Printable<typename T::value_type>
{
  for (auto x : t) {
    print(x);
    std::cout << " ";
  }
  std::cout << std::endl;
}

template <typename T> class A {
protected:
  T x;

public:
  A(T x = T()) : x(x) {}
  void print() const { std::cout << "[" << x << "]"; }
  friend A operator+(const A &a, const A &b) { return a.x + b.x; }
};

template <typename T> class B : public A<T> {
public:
  using A<T>::A;
  B(const A<T> &a) : A<T>(a) {}
  friend std::ostream &operator<<(std::ostream &out, const B &b) {
    return (out << "#" << b.x << "#");
  }
};

template <typename T> T sum(const std::vector<T> &v) {
  T s = T();
  for (auto x : v) {
    s = s + x;
  }
  return s;
}

int main() {
  std::vector v{1, 2, 4, 5};
  print(v);
  A<int> a{5};
  print(a);
  std::cout << std::endl;
  B<double> b{3.14};
  print(b);
  std::cout << std::endl;
  print(2.7);
  std::cout << std::endl;
  std::vector<A<int>> va{4, 5, 7, 9};
  std::vector<B<int>> vb{4, 5, 7, 9};
  print(va);
  std::cout << std::endl;
  print(vb);
  std::cout << std::endl;
  print(sum(v));
  std::cout << std::endl;
  print(sum(vb));
  std::cout << std::endl;
  return 0;
}
/**
* Expected output
0 : 1
1 : 2
2 : 4
3 : 5
-------
[5]
#3.14#
2.7
0 : [4]
1 : [5]
2 : [7]
3 : [9]
-------
0 : #4#
1 : #5#
2 : #7#
3 : #9#
-------
12
#25#
*/