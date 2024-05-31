#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <typename Container> void print(const Container &c) {
  // 1.  Print elements of the container separated by ", "
  //     using std::copy and std::ostream_iterator
  //  <<>> (1 line)
  std::copy(
      c.begin(), c.end(),
      std::ostream_iterator<typename Container::value_type>(std::cout, ", "));
  std::cout << std::endl;
}

/**
 * Removes all non alphanumeric characters from given word and converts to lower
 * case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string &s1) {
  // 2. Implement using stl algorithms only
  //    Hint: use remove_if, transform, erase
  s1.erase(
      std::remove_if(s1.begin(), s1.end(), [](char c) { return !isalpha(c); }),
      s1.end());
  std::cout
      << std::transform(s1.begin(), s1.end(), s1.begin(), tolower).operator->()
      << std::endl;
}
/**
  Checks if the first word is an anagram of the second word.

     - All non alphanumeric chars are ignored (remove them).
     - It is case insensitive (convert to lower case).
     - Words cannot be the same (at least one change needed).
     - They should contain the same letters (sort letters in each word to
  compare).

  @param word1 not empty string
  @param word2 not empty string
  @return true if and only if word1 is an anagram of word2.
*/
bool isAnagram(std::string word1, std::string word2) {
  // 3. Implement isAnagram function using stl algorithms only
  //    Hint: use toLowerAlpha, sort, equal
  //  <<>> (several lines)
  std::string newWord1, newWord2;
  std::copy_if(word1.begin(), word1.end(), newWord1.begin(), isalpha);
  std::copy_if(word2.begin(), word2.end(), newWord2.begin(), isalpha);
  toLowerAlpha(newWord1);
  toLowerAlpha(newWord2);
  std::sort(newWord1.begin(), newWord1.end());
  std::sort(newWord2.begin(), newWord2.end());
  return newWord1 == newWord2;
}
void isAnagramTest(const std::string &s1, const std::string &s2,
                   bool expected) {
  std::cout << "isAnagram(\"" << s1 << "\", \"" << s2 << "\") = ";
  bool result = isAnagram(s1, s2);
  std::cout << std::boolalpha << result
            << ((result == expected) ? " [OK]" : " [ERROR]") << std::endl;
}
int main() {

  constexpr int N = 10;
  std::vector<int> v(N);

  // 4. Fill vector v with consecutive numbers starting with -5. (Hint: use
  // std::iota)
  //  <<>> (1 line)
  std::iota(v.begin(), v.end(), -5);
  print(v);

  std::vector<int> odd;
  // 5. Copy to odd all odd numbers from v (Hint: use copy_if and back_inserter)
  //  <<>> (1 line)
  std::copy_if(v.begin(), v.end(), std::back_inserter(odd),
               [](int x) { return std::abs(x) % 2 == 1; });
  print(odd);

  // 6. Each number x in v replace with x*x-1 (Hint std::transform)
  //  <<>> (1 line)
  std::transform(v.begin(), v.end(), v.begin(),
                 [](int x) { return x * x - 1; });
  print(v);

  std::vector<int> intersect;
  // 7. Sort v and compute intersection of vectors odd and v (treated as sets)
  //  <<>> (2 lines)
  std::sort(v.begin(), v.end());
  std::set_intersection(odd.begin(), odd.end(), v.begin(), v.end(),
                        std::back_inserter(intersect));
  print(intersect);

  isAnagramTest("male", "lame", true);
  isAnagramTest(" Ala $%", "%%Ala%%ska%", false);
  isAnagramTest(" Ala $%", "%%la%%a%", true);
  isAnagramTest("A l a", "ALA", false);
}
/* Expected output
 *
-5, -4, -3, -2, -1, 0, 1, 2, 3, 4,
-5, -3, -1, 1, 3,
24, 15, 8, 3, 0, -1, 0, 3, 8, 15,
-1, 3,
isAnagram("male", "lame") = true [OK]
isAnagram(" Ala $%", "%%Ala%%ska%") = false [OK]
isAnagram(" Ala $%", "%%la%%a%") = true [OK]
isAnagram("A l a", "ALA") = false [OK]
 */
