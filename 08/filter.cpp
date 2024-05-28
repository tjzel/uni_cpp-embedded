#include "Filter.h"
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {

  // Function for debugging
  bool debug = true;
  auto message = [&debug](int x, bool v) {
    if (debug and !v)
      cout << " - skipping " << x << endl;
    return v;
  };
  auto addMessage = [message](auto f) {
    return [message, f](int x) { return message(x, f(x)); };
  };

  // Predicates
  auto isOdd = [](int x) { return x % 2 == 1; };
  auto isPrime = [](int x) {
    if (x <= 1)
      return false;
    for (auto i = 2; i * i <= x; ++i)
      if (x % i == 0)
        return false;
    return true;
  };

  // Data
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 23};

  // Filters
  auto even = make_filter(v, addMessage(isOdd));

  auto evenPrime = make_filter(even, addMessage(isPrime));

  v[2] = 1001;
  v.push_back(101);

  for (auto x : evenPrime) {
    cout << x << endl;
  }
  cout << "=======================\n";
  auto primeOdd = make_filter(make_filter(v, isPrime), isOdd);
  for (auto x : primeOdd) {
    cout << x << endl;
  }
  cout << "=======================\n";
  auto evenPrimeWithOne = make_filter(evenPrime, [](int x) {
    while (x != 0)
      if (x % 10 == 1)
        return true;
      else
        x /= 10;
    return false;
  });
  debug = false;
  for (auto x : evenPrimeWithOne) {
    cout << x << endl;
  }
  return 0;
}

/*
 * Expected output
 - skipping 1
 - skipping 2
 - skipping 1001
 - skipping 4
5
 - skipping 6
7
 - skipping 8
 - skipping 9
 - skipping 10
11
 - skipping 12
13
 - skipping 14
 - skipping 15
23
101
=======================
5
7
11
13
23
101
=======================
11
13
101
*/
