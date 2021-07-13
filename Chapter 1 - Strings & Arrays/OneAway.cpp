/** One Away:
 * There are 3 types of edits that can be performed on strings: 
 * insert a character, remove a character, or replace a character. 
 * Given two strings, write a function to check if they are one edit 
 * (or zero edits) away.
 */

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>

bool oneAway(const std::string& s1, const std::string& s2) {
  // Strings that are the same are 0 edits away.
  if(s1 == s2) return true;

  // Lengths are too different to be 1 edit away.
  int l1 = s1.length();
  int l2 = s2.length();
  if(std::abs(l1 - l2) > 1) return false;

  // If strings are the same length, count differences.
  // If there is more than 1, strings can't be 1 edit away.
  if(l1 == l2) {
    int differenceCount = 0;
    for(int i = 0; i < l1 && differenceCount <= 1; ++i) {
      if(s1[i] != s2[i]) 
        differenceCount++;
    }
    return differenceCount <= 1;
  }

  // Try deleting characters from longer string
  // and see if it matches the shorter string.
  else {
    std::string s_long = (l1 > l2) ? s1 : s2;
    std::string s_short = (l1 < l2) ? s1 : s2;
    int L = std::max(l1, l2);

    for(int i = 0; i < L; ++i) {
      std::string edit_delete = s_long;
      edit_delete.erase(i, 1);
      if(edit_delete == s_short) {
        return true;
      }
    }
    return false;
  }
}


int main() {
  // Test from file
  std::ifstream testFile("OneAway_test.txt");
  if(testFile.is_open()) {
    std::string line;
    while(std::getline(testFile, line)) {
      std::stringstream ss(line);
      std::string s1, s2, result;
      if(!(ss >> s1 >> s2)) { break; } // break on bad read (end-of-file)
      result = oneAway(s1, s2) ? "true" : "false";
      std::printf("%s %s => %s\n", s1.c_str(), s2.c_str(), result.c_str());
    }
  }
  // Test hardcoded strings
  // std::string s1 = "drone";
  // std::string s2 = "done";
  // std::string result = oneAway(s1, s2) ? "true" : "false";
  // std::cout << result << '\n';
}