#include <iostream>
#include <vector>

template <typename T, typename = void> struct hasSize : std::false_type {};

template <typename T>
struct hasSize<T, std::void_t<decltype(std::declval<T>().size())>>
    : std::true_type {};

template <typename T, typename = void> struct hasValueType : std::false_type {};

template <typename T>
struct hasValueType<T, std::void_t<typename T::value_type>> : std::true_type {};

namespace enable_if {

template <typename T>
typename std::enable_if_t<hasSize<std::remove_reference_t<T>>::value and
                              hasValueType<std::remove_reference_t<T>>::value,
                          size_t>
getSize(T &&t) {
  return t.size() * sizeof(typename std::remove_reference_t<T>::value_type);
}

template <typename T>
typename std::enable_if_t<!hasSize<std::remove_reference_t<T>>::value and
                              !hasValueType<std::remove_reference_t<T>>::value,
                          size_t>
getSize(T &&t) {
  return sizeof(t);
}

} // namespace enable_if

namespace ifconstexpr {
template <typename T> size_t getSize(T &&x) {
  if constexpr (hasSize<std::remove_reference_t<T>>::value and
                hasValueType<std::remove_reference_t<T>>::value) {
    return x.size() * sizeof(typename std::remove_reference_t<T>::value_type);
  } else {
    return sizeof(x);
  }
}
} // namespace ifconstexpr

int main(void) {
  std::cout << std::boolalpha;
  std::cout << hasSize<int>::value << std::endl;                   // false
  std::cout << hasSize<std::vector<int>>::value << std::endl;      // true
  std::cout << hasValueType<int>::value << std::endl;              // false
  std::cout << hasValueType<std::vector<int>>::value << std::endl; // true

  std::vector<int> v{1, 2, 3, 4, 5};
  std::cout << enable_if::getSize(5) << std::endl;   // 4
  std::cout << enable_if::getSize(v) << std::endl;   // 20
  std::cout << ifconstexpr::getSize(5) << std::endl; // 4
  std::cout << ifconstexpr::getSize(v) << std::endl; // 20
}