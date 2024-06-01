
#include <type_traits>

#include <iomanip>
#include <iostream>

template <int... Rest> struct IntegerList;

template <int Index, typename List> struct getInt;

template <typename List> struct Max;

template <int Head, int... Rest> struct IntegerList<Head, Rest...> {
  typedef IntegerList<Rest...> RestList;
  static constexpr int value = Head;

  static constexpr int get(int index) {
    if (index == 0) {
      return Head;
    }
    else {
      return RestList::get(index - 1);
    }
  }

  static constexpr int max() {
    return Max<IntegerList<Head, Rest...>>::value;
  }
};

template <int Head> struct IntegerList<Head> {
  static constexpr int value = Head;

  static constexpr int get(int index) { return Head; }

  static constexpr int max() { return Head; }
};


template <int Index, int Head, int... Rest>
struct getInt<Index, IntegerList<Head, Rest...>> {
  static constexpr int value = Index == 0 ? Head : IntegerList<Rest...>::get(Index - 1);
};

template <int Head, int... Rest>
std::ostream& operator<<(std::ostream& os,
  const IntegerList<Head, Rest...>& list) {
  os << Head;
  if constexpr (sizeof...(Rest) > 0) {
    os << ", ";
    return operator<<(os, IntegerList<Rest...>());
  }
  return os;
}

template <typename List> struct IsSorted;

template <int Head, int... Rest> struct IsSorted<IntegerList<Head, Rest...>> {
  static constexpr bool value = (Head <= IntegerList<Rest...>::value) && IsSorted<IntegerList<Rest...>>::value;
};

template <int Head> struct IsSorted<IntegerList<Head>> {
  static constexpr bool value = true;
};

template <int Head, int... Rest> struct Max<IntegerList<Head, Rest...>> {
  static constexpr int value = Head > Max<IntegerList<Rest...>>::value ? Head : Max<IntegerList<Rest...>>::value;
};

template <int Head> struct Max<IntegerList<Head>> {
  static constexpr int value = Head;
};

template <typename LeftList, typename RightList> struct Join;

template <int HeadLeft, int... RestLeft, int HeadRight, int... RestRight>
struct Join<IntegerList<HeadLeft, RestLeft...>, IntegerList<HeadRight, RestRight...>> {
  using type = IntegerList<HeadLeft, RestLeft..., HeadRight, RestRight...>;
};



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
  cout << "Is A sorted? " << IsSorted<listA>::value << endl;
  cout << "Is B sorted? " << IsSorted<listB>::value << endl;

  using listC = Join<listA, listB>::type;

  cout << "List C : " << listC() << endl;
  cout << Max<listC>::value << endl;
  cout << listC::max() << endl;
  static_assert(listC::max() == 9);
  static_assert(listA::max() == 5);
}