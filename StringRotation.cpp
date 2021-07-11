/*
String Rotation:
Assume you have a method isSubstring which checks 
if one word is a substring of another. Given two strings s1 and s2, 
write code to check if s2 is a rotation of s1 
using only one call to isSubstring.
*/

#include <iostream>
#include <string>

// Forward declare
bool isSubstring(const std::string& s1, const std::string& s2);

/*Idea:
If s1 and s2 are rotations of each other, it's possible to group s1 and s2
into 2 substrings X and Y in opposite orders.

  s1 = pikachu = (pika)(chu) = (X)(Y)
  s2 = chupika = (chu)(pika) = (Y)(X)

Notice s2 concatenated with itself (s2 + s2) contains s1 as a subtring.

  s2 + s2 = chupikachupika = (chu)(pika)(chu)(pika) = (Y)(X)(Y)(X)
               ^^^^^^^                                   ^^^^^^
     s1 is a substring of s2 + s2               XY is a substring of YXYX
*/
bool isRotation(const std::string& s1, const std::string& s2) {
  return isSubstring(s1, s2 + s2);
}


// Is s1 a substring of s2 ?
bool isSubstring(const std::string& s1, const std::string& s2) {
  int l1 = s1.length();
  int l2 = s2.length();
  // s1 cannot be a substring if it is longer than s2
  if(l1 > l2) return false;

  // Use i as a starting index in s2 and 0 <= j <= l1 as index for s1
  // Compare characters s1 in s2 to those in s2, at i offset by j.
  //
  //        s2                      s1
  // 0  1  2  3 ... l2         0  1  2 ... l1
  //    |->|->|                |->|->|
  //    i    i+j                     j
  //
  // Find range for i so (i + j) is in bounds of s2.
  // 0 <= i +    j   <= l2-1
  // 0 <= i + (l1-1) <= l2-1
  // 0 <= i          <= l2 - l1
  
  for(int i = 0; i <= l2 - l1; ++i) {
    bool match = true;
    for(int j = 0; j < l1; ++j) {
      if (s1[j] != s2[i + j]) {
        match = false;
        break;
      }
    }
    if(match) return true;
  }
  return false;
}


int main() {
  // Test hardcoded string
  std::string result = isRotation("pikachu", "chupika") ? "true" : "false";
  std::cout << result << '\n';
}
