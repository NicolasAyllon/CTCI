/** Palindrome Permutation:
 * Given a string, write a function to check if it is a permutation of a
 * palindrome. The palindrome does not need to be limited to English words.
 * 
 * Example:
 * Input: "tact coa"
 * Output: True (permutations: "taco cat", "atco cta", ...)
 */

#include<iostream>
#include<string>
#include<array>

bool isLetter(const char c);
int letterToIndex(const char c);

// Idea:
// In a palindrome with an even number of letters, 
// the frequency of all letters must be even.
// In a palindrome with an odd number of letters,
// at most 1 letter can have an odd frequency.
//
// Method:
// Build a frequency table using std::array counting only letters
// Then, if the number of letters is even
// iterate through table to check that all frequencies are even
// Or, if the number of letters is odd
// check that at most 1 letter has an odd frequency.
bool palindromePermutation(const std::string& s) {
  // Build frequency table and count letters
  std::array<int, 26> f_table = {};
  int numLetters = 0;
  for(char c : s) {
    if(isLetter(c)) {
      f_table[letterToIndex(c)]++;
      numLetters++;
    }
  }
  
  // Test frequency table:
  // for(char c = 'a'; c <= 'z'; ++c) { std::cout << c << " "; }
  // std::cout << '\n';
  // for(int f: f_table) { std::cout << f << " "; }

  // If the number of letters is odd
  // Allow at most one frequency to be odd.
  // Afterwards (and when the number of letters is even)
  // the letter frequencies must be even.

  bool hasOddLength = (numLetters % 2 == 1);
  bool allowOddFrequency = hasOddLength ? true : false;

  for(int frequency : f_table) {
    if(frequency % 2 == 1) {
      if(allowOddFrequency) {
        // One letter has been allowed to have odd frequency, no more.
        allowOddFrequency = false;
      } 
      else { // allowOddFrequency is false
        return false;
      }
    }
  }
  return true;
}

// Helping functions
bool isLetter(const char c) {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

int letterToIndex(const char c) {
  if('a' <= c && c <= 'z') {
    return c - 'a';
  } else if('A' <= c && c <= 'Z') {
    return c - 'A';
  } else {
    return -1;
  }
}


int main() {
  // Test with user input:
  std::string line;
  std::cout << "Enter a string: " << '\n';
  std::getline(std::cin, line);
  std::string result = palindromePermutation(line) ? "true" : "false";
  std::cout << result << '\n';
}
