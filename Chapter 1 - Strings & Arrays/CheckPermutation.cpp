/**
 * Check Permutation:
 * Given two strings, write a method to decide if 
 * one is a permutation of the other.
 */
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>

// Idea: 
// Two strings are permutations of each other if the frequency 
// of each letter is the same.
// For example, 'loves' and 'solve' are permutations, and both have 
// e => 1
// l => 1
// o => 1
// s => 1
// v => 1
// Method:
// Use std::map to build frequency tables for both strings.
// Then compare maps with std::map's built-in operator==.
bool checkPermutation(const std::string& s1, const std::string& s2) {
  // Vacuously true when both strings are empty
  if(s1.empty() && s2.empty()) return true;
  // Strings of different lengths can't be permutations
  if(s1.length() != s2.length()) return false;
  
  // Build frequency tables for both strings
  std::map<char, int> f_table1; // for s1
  std::map<char, int> f_table2; // for s2
  // Build frequency table for s1
  for(char c: s1) {
    if(f_table1.find(c) != f_table1.end()) {
      f_table1[c]++;
    }
    else {
      f_table1[c] = 0;
    }
  }
  // Build frequency table for s2
  for(char c: s2) {
    if(f_table2.find(c) != f_table2.end()) {
      f_table2[c]++;
    }
    else {
      f_table2[c] = 0;
    }
  }
  // Use operator== to determine whether the frequency tables are the same
  return f_table1 == f_table2;
}


int main() {
  std::ifstream testFile("CheckPermutation_test.txt");
  if(testFile.is_open()) {
    std::string line;
    while(std::getline(testFile, line)) {
      std::stringstream ss(line);
      std::string s1, s2;
      if(!(ss >> s1 >> s2)) { break; } // break on error
      std::string result = checkPermutation(s1, s2) ? "true" : "false";
      std::cout << line << " " << result << '\n';
    }
  }
  else std::cout << "Unable to open file" << '\n';
}