#include <iostream>
#include <map>
#include <vector>
using namespace std;

/**
 * Removes all non alphanumeric characters from given word and converts to lower
 * case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string &s1) {

  s1.erase(remove_if(s1.begin(), s1.end(), [](char c) { return !isalnum(c); }),
           s1.end());
  std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
}

int main() {
  std::string word;
  map<string, int> c;
  while (cin >> word) {
    toLowerAlpha(word);

    if (word != "") {
      c[word]++;
    }
  }
  // ...
  multimap<int, string> m2;

  for (auto it = c.begin(); it != c.end(); ++it) {
    m2.insert(make_pair(it->second, it->first));
  }

  int i = 0;
  cout << "Number of distinct words : " << c.size() << endl;
  cout << "\nThe top 20 most popular words: \n";
  for (auto it = --m2.end(); it != m2.begin() && i < 20; --it, ++i) {
    cout << it->second << " : " << it->first << endl;
  }
  // ...
  return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4726

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248
your : 242

 */