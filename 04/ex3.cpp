#include <deque>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

bool biggerThan5(int x) { return x > 5; }

/// TODO
template <template <typename Element, typename Alloc> typename TOutContainer,
          typename TElement, typename TAlloc,
          template <typename Element, typename Alloc> typename TInContainer,
          typename TPredicate>
TOutContainer<TElement, TAlloc>
selectIf(TInContainer<TElement, TAlloc> container, TPredicate predicate) {
  auto result = TOutContainer<TElement, TAlloc>();
  for (auto c : container) {
    if (predicate(c)) {
      result.push_back(c);
    }
  }
  return result;
}

int main() {
  auto print = [](auto v) {
    for (auto x : v)
      cout << x << " ";
    cout << endl;
  };

  std::vector<int> v = {1, 2, 13, 4, 5, 54};
  std::list<int> result = selectIf<std::list>(v, biggerThan5);
  print(result); //  13 54

  auto result2 = selectIf<std::deque>(v, [](int x) -> bool { return x % 2; });
  print(result2); //  1 13 5

  auto result3 = selectIf<std::vector>(result2, biggerThan5);
  print(result3); //  13
  return 0;
}