
#include <type_traits>

#include <iomanip>
#include <iostream>

template <int N, int... Rest> struct IntegerList;

template <int N, typename IIntegerList> struct getInt;

template <int N, int... Rest> struct IntegerList {
  typedef IntegerList<Rest...> RestList;
  static constexpr int value = N;

  static constexpr int get(int index) {
    if (index == 0) {
      return N;
    } else {
      return RestList::get(index - 1);
    }
  }
};

template <int N> struct IntegerList<N> {
  static constexpr int value = N;

  static constexpr int get(int index) { return N; }
};

template <int N, typename IIntegerList> struct getInt {
  static constexpr int value =
      getInt<N - 1, typename IIntegerList::RestList>::value;
};

template <typename IIntegerList> struct getInt<0, IIntegerList> {
  static constexpr int value = IIntegerList::value;
};

template <int N, int... Rest>
std::ostream &operator<<(std::ostream &os,
                         const IntegerList<N, Rest...> &list) {
  os << N;
  if constexpr (sizeof...(Rest) > 0) {
    os << ", ";
    return operator<<(os, IntegerList<Rest...>());
  }
  return os;
}

template <int IIntegerList> struct IsSorted {};

using namespace std;
int main() {

  using listA = IntegerList<5, -1, 5, 2, 1>;
  using listB = IntegerList<1, 4, 6, 9>;
  cout << "List A : " << listA() << endl;
  cout << "List B : " << listB() << endl;

  cout << "A[1] = " << getInt<1, listA>::value << endl;
  cout << "B[3] = " << listB::get(3) << endl;
  static_assert(getInt<1, listA>::value == -1);
  static_assert(listB::get(3) == 9);
  static_assert(listB::get(1) == 4);

  cout << boolalpha;
  // cout << "Is A sorted? " << IsSorted<listA>::value << endl;
  // cout << "Is B sorted? " << IsSorted<listB>::value << endl;

  // using listC = Join<listA, listB>::type;

  // cout << "List C : " << listC() << endl;
  // cout << Max<listC>::value << endl;
  // cout << listC::max() << endl;
  // static_assert(listC::max() == 9);
  // static_assert(listA::max() == 5);
}