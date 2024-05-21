#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <iostream>
#include <iterator>
#include <numeric>
#include <semaphore>
#include <thread>
#include <utility>
#include <vector>
using namespace std;

template <int N> struct Array {
  int a[N];
  int value = 1;
  long long sum = 0;
  int index = 0;
  std::mutex indexLock;
  std::mutex randLock;
  std::mutex semaphoreLock;
  std::atomic_bool wasComputed = false;
  int fillSemaphore = 1;
  int sumSemaphore = 0;

  Array(int numberOfThreads) : fillSemaphore(numberOfThreads) {}

  int f(int x) {
    int y = x % 11;
    return (y * y + 1);
  }

  void generateArray() {
    int i = getAndIncrementIndex();
    while (i < N) {
      a[i] = getRand();
      i = getAndIncrementIndex();
    }

    {
      std::lock_guard<std::mutex> lock(semaphoreLock);
      if (fillSemaphore == 1) {
        resetIndex();
      }
      fillSemaphore--;
    }

    while (fillSemaphore > 0) {
      // Wait until it's filled.
    }

    i = getAndIncrementIndex();
    while (i < N) {
      a[i] = f(a[i]);
      i = getAndIncrementIndex();
    }
  }

  inline int getRand() {
    std::lock_guard<std::mutex> lock(randLock);
    return rand();
  }

  inline int getAndIncrementIndex() {
    std::lock_guard<std::mutex> lock(indexLock);
    return index++;
  }

  inline void resetIndex() {
    std::lock_guard<std::mutex> lock(indexLock);
    index = 0;
  }

  inline void acquireSumSemaphore() {
    std::lock_guard<std::mutex> lock(semaphoreLock);
    if (sumSemaphore == 0) {
      sum = 0;
    }
    sumSemaphore++;
  }

  inline void releaseSumSemaphore(int localSum) {
    sum += localSum;
    std::lock_guard<std::mutex> lock(semaphoreLock);
    sumSemaphore--;
  }

  long long computeSum() {
    if (wasComputed) {
      return sum;
    }
    acquireSumSemaphore();
    int localSum = 0;
    for (int x : a) {
      localSum += x;
    }
    releaseSumSemaphore(localSum);
    while (sumSemaphore > 0) {
      // Wait until all is added up.
    }
    wasComputed = true;
    return sum;
  }
};

int main() {
  srand(2019);
  using A = Array<1000>;
  A array(2);
  std::thread t1(&A::generateArray, &array);
  //  What happens if you uncomment this line?
  std::thread t2(&A::generateArray, &array);
  t2.join();
  t1.join();
  for (int i = 0; i < 40; i++) {
    cout << array.a[0 + i] << "  ";
  }
  std::cout << std::endl;
  std::thread t3([&]() { std::cout << array.computeSum() << " "; });
  std::thread t4([&]() { std::cout << array.computeSum() << " "; });
  long long sum = array.computeSum();
  cout << "\n sum = " << sum << endl;
  t3.join();
  t4.join();
}