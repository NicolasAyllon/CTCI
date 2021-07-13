/*
String Compression:
Implement a method to perform basic string compression using the counts of
repeated characters.

"aabccccaaa" -> "a2b1c5a3"

If the result is not shorter than the original string, return the original.

"abcde" -> "abcde" (not "a1b1c1d1e1")
*/
#include<iostream>
#include<fstream>
#include<string>

bool isDigit(char c);
int charToInt(char c);

std::string compressRepeats(const std::string& s) {
  // Immediately return string if empty
  if(s.empty()) return s;

  std::string s_compressed = "";
  char currentChar = s[0];
  int count = 1;

  // Build compressed string
  for(int i = 1; i < s.length(); ++i) {
    if(s[i] != currentChar) {
      s_compressed += currentChar + std::to_string(count);
      currentChar = s[i];
      count = 1;
    }
    else { // s[i] == currentChar
      count++;
    }
  }
  // add final character and count
  s_compressed += currentChar + std::to_string(count);
  // Return either the original or compressed, whichever is shorter.
  return (s_compressed.length() < s.length() ? s_compressed : s);
}


// Additional uncompress function:
// implemented for fun and completeness
std::string uncompressRepeats(const std::string& s) {
  if(s.empty()) return s;

  char currentChar = s[0];
  bool numMode = false;
  int currentNum = 1;
  std::string result = "";

  for(int i = 0; i < s.length(); ++i) {
    if(isDigit(s[i])) {
      if(!numMode) {
        numMode = true;
        currentNum = charToInt(s[i]);
      }
      else {
        // Calculate numeric result of appending digit s[i]. 
        // Example: "9"->"95" calculate 10*9 + 5 = 95
        currentNum = 10*currentNum + charToInt(s[i]);
      }
    }
    // Non-number character read (letter)
    else {
      if(numMode) {
        numMode = false;
        // append remaining copies of currentChar
        std::string part(currentNum-1, currentChar);
        result += part;
        // apppend first copy of new char, and set as currentChar
        result += s[i];
        currentChar = s[i];
      }
      else {
        result += s[i];
      }
    }
  }
  // If the last character read was a digit, append remaining copies.
  // (If it was a letter, it's already been appended.)
  if(numMode) {
    std::string part(currentNum-1, currentChar);
    result += part;
  }
  return result;
}


bool isDigit(char c) {
  return ('0' <= c && c <= '9');
}

int charToInt(char c) {
  return c - '0';
}


int main() {
  // Test from file
  std::ifstream testFile("StringCompression_test.txt");
  if(testFile.is_open()) {
    std::string line, compressed, uncompressed;
    while(std::getline(testFile, line)) {
      compressed = compressRepeats(line);
      uncompressed = uncompressRepeats(compressed);
      std::cout << 
        line << " -> " << compressed << " -> " << uncompressed << '\n';
    }
  }
  // Test hardcoded string
  // std::string s = "hellooooo";
  // std::cout << compressRepeats(s) << '\n';
  // std::string s2 = "a5b3";
  // std::cout << uncompressRepeats(s2) << '\n';
}
