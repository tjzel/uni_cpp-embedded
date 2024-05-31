#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Trie;
/**
 * Trie structure
 *
 * HINT: use std::map to implement it!
 *       My implementation adds less than 25 lines of code.
 */
class Trie {
  std::map<std::string, Trie> children;

  void add_(const std::vector<std::string> &sentence) {
    auto word = sentence.front();
    std::vector<std::string> copyOfSentence;
    std::copy(++sentence.begin(), sentence.end(),
              std::back_inserter(copyOfSentence));
    if (!children.contains(word)) {
      children[word] = Trie();
    }
    if (!copyOfSentence.empty()) {
      children[word].add_(copyOfSentence);
    }
  }

  void printEndings(const std::vector<std::string> &sentence,
                    std::vector<std::string> &forwardSentence) {
    if (!sentence.empty()) {
      auto word = sentence.front();
      std::vector<std::string> copyOfSentence;
      std::copy(++sentence.begin(), sentence.end(),
                std::back_inserter(copyOfSentence));

      if (children.contains(word)) {
        children[word].printEndings(copyOfSentence, forwardSentence);
      }
    } else {
      if (children.empty()) {
        std::cout << " < ";
        printSentence(forwardSentence);
        cout << "\n";
      } else {
        for (auto &record : children) {
          forwardSentence.push_back(record.first);
          record.second.printEndings(sentence, forwardSentence);
          forwardSentence.pop_back();
        }
      }
    }
  }

public:
  static void printSentence(const std::vector<std::string> &sentence) {
    for (const auto &w : sentence) {
      cout << w << " ";
    }
  }

  void add(const std::vector<std::string> &sentence) {
    cout << "Adding : ";
    printSentence(sentence);
    cout << "\n";
    add_(sentence);
  }

  void
  printPossibleEndings(const std::vector<std::string> &beginningOfSentence) {
    cout << "Endings for \"";
    printSentence(beginningOfSentence);

    cout << "\" are :\n";

    std::vector<std::string> forwardSentence;
    printEndings(beginningOfSentence, forwardSentence);
  }

  void load(const std::string &fileName) {
    ifstream file(fileName);
    if (!file) {
      cerr << "Error when openning file " << fileName << endl;
      return;
    }
    string word;
    vector<string> sentence;
    while (file >> word) {
      sentence.push_back(word);
      // is it end of the sentence?
      if (word.find_last_of('.') != string::npos) {
        add(sentence);
        sentence.clear();
      }
    }
  }
};

int main() {
  Trie dictionary;
  dictionary.load("./sample.txt");
  // dictionary.load("hamletEN.txt");

  dictionary.printPossibleEndings({"Curiosity"});
  dictionary.printPossibleEndings({"Curiosity", "killed"});
  dictionary.printPossibleEndings({"The", "mouse", "was", "killed"});

  /* cout << "Beginning of sentence (ended with single .): ";
  string word;
  vector<string> sentence;
  while(true){
      cin >> word;
      if(word == ".")
          break;
      sentence.push_back(word);
      dictionary.printPossibleEndings(sentence);
  }*/
  return 0;
}
/* Expected output:
Adding : Curiosity killed the cat.
Adding : Curiosity killed the mouse.
Adding : Curiosity saved the cat.
Adding : Curiosity killed the cat and the mouse.
Adding : The cat was killed by curiosity.
Adding : The mouse was killed by cat.
Adding : The mouse was killed by curiosity.
Endings for "Curiosity " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.
 > saved the cat.

Endings for "Curiosity killed " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.

Endings for "The mouse was killed " are :
 > by cat.
 > by curiosity.

 */