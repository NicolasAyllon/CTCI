/**
 * Is Unique:
 * Implement an algorithm to determine if a string has all unique characters.
 * What if you cannot use additional data structures?
 */
#include <iostream>
#include <fstream>
#include <string>

bool allCharactersUnique(const char* s);
int letterToIndex(char c);

// Without additional data structures
bool allCharactersUnique(const char* s) {
  int frequencyTable[26] = {}; // [0,0,...0]
  while(*s != '\0') {
    if(frequencyTable[letterToIndex(*s)] > 0) {
      return false;
    }
    frequencyTable[letterToIndex(*s)]++;
    s++;
  }
  return true;
}

// Returns an index for characters a-z or A-Z from 0 to 25
// It is case-insensitive: A or a => 0, B or b => 1, ..., Z or z => 25
int letterToIndex(char c) {
  if('a' <= c && c <= 'z') {
    return c - 'a';
  } else if ('A' <= c && c <= 'Z') {
    return c - 'A';
  } else {
    return -1;
  }
}

int main () {
  // Test on a file
  std::ifstream testFile("IsUnique_test.txt");
  if(testFile.is_open()) {
  std::string line;
    while(std::getline(testFile, line)) {
      std::string result = allCharactersUnique(line.c_str()) ? "true" : "false";
      std::cout << line << ": " << result << '\n';
    }
    testFile.close();
  }
  else std::cout << "Unable to open file" << '\n';

  // Test on a single word
  // const int streamsize = 80;
  // char input[streamsize];
  // std::cout << "Enter a word: ";
  // std::cin.getline(input, streamsize, '\n');
  // //std::cout << input << '\n';
  // std::string result = allCharactersUnique(input) ? "true" : "false";
  // std::cout << "result: " << result << '\n';
  return 0;
}
