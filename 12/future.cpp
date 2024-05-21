#include <fstream>
#include <future>
#include <iostream>
#include <vector>

std::future<long long> getSumForFile(const std::string &fileName) {
  auto file = std::make_shared<std::ifstream>(fileName);

  std::promise<long long> promise;

  auto future = promise.get_future();

  std::thread([file, localPromise = std::move(promise)]() mutable {
    long long sum = 0;
    char c;
    while (file->get(c)) {
      sum += c;
    }
    localPromise.set_value(sum);
  }).detach();

  return future;
}

int printDuplicateSums(
    const std::vector<std::pair<std::string, long long>> &fileNamesWithSums) {
  std::vector<long long> duplicateSums;
  for (size_t i = 0; i < fileNamesWithSums.size(); i++) {
    for (size_t j = i + 1; j < fileNamesWithSums.size(); j++) {
      if (fileNamesWithSums[i].second == fileNamesWithSums[j].second) {
        duplicateSums.push_back(fileNamesWithSums[i].second);
      }
    }
  }
  if (duplicateSums.size() > 0) {
    std::cout << "Duplicate sums: ";
    for (auto sum : duplicateSums) {
      std::cout << sum << " ";
    }
    std::cout << std::endl;
  }
  return duplicateSums.size();
}

int main(int argc, char *argv[]) {
  std::vector<std::pair<std::string, long long>> fileNamesWithSums;

  for (int i = 1; i < argc; i++) {
    fileNamesWithSums.push_back({argv[i], 0});
  }

  std::vector<std::pair<size_t, std::future<long long>>> futures;

  for (size_t i = 0; i < fileNamesWithSums.size(); i++) {
    futures.push_back({i, getSumForFile(fileNamesWithSums[i].first)});
  }

  for (auto &[i, future] : futures) {
    auto sum = future.get();
    fileNamesWithSums[i].second = sum;
  }

  for (auto &[i, sum] : fileNamesWithSums) {
    std::cout << i << ": " << sum << std::endl;
  }

  return 0;
}