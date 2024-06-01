#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

template <typename Set, typename = void>
struct hasRandomAccess : std::false_type {};

template <typename Set>
struct hasRandomAccess<Set, std::void_t<decltype(std::declval<Set>()[0])>>
    : std::true_type {};

template <typename Set> double median(Set set) {
  return medianImpl(set, hasRandomAccess<Set>{});
}

template <typename Set> double medianImpl(Set set, std::true_type) {
  std::sort(set.begin(), set.end());
  if (set.size() == 0) {
    return 0;
  } else if (set.size() % 2 == 0) {
    return (set[set.size() / 2 - 1] + set[set.size() / 2]) / 2.0;
  } else {
    return set[set.size() / 2];
  }
}
template <typename Set> double medianImpl(Set set, std::false_type) {
  set.sort();
  if (set.size() == 0) {
    return 0;
  } else if (set.size() % 2 == 0) {
    auto it = set.begin();
    std::advance(it, set.size() / 2 - 1);
    return (*it + *(++it)) / 2.0;
  } else {
    auto it = set.begin();
    std::advance(it, set.size() / 2);
    return *it;
  }
}

int main(void) {
  std::list<int> a{3, 2, 5, 1, 4};
  std::cout << median(a) << std::endl; // 3
  std::vector<int> v{3, 1, 4, 2};
  std::cout << median(v) << std::endl; // 2.5
}