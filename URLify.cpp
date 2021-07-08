/** URLify:
 * Write a method to replace all the spaces in a string with '%20'.
 * You may assume that the string has sufficient space at the end to hold the
 * additional characters, and that you are given the "true" length 
 * of the string. (Note: If you are implementing in Java, please use a
 * character array so that you can perform this operation in place.)
 */

#include <iostream>

// Modify c-string s so that spaces ' ' are replaced with "%20"
// Note: Max input size: char[256]
char* URLify(char* s) {
  // Create copy of s
  char s_copy[256];
  strcpy(s_copy, s);
  // Get pointers to start of s and s_copy
  char* current_s_copy = s_copy; 
  char* current_s = s;
  // Declare replacement and its length
  char replacement[] = "%20";
  int replacementLength = strlen(replacement);

  // Iterate through s_copy and overwrite contents of s, 
  // replacing ' ' with "%20" 
  while(*current_s_copy != '\0') {
    if(*current_s_copy == ' ') {
      strcpy(current_s, replacement);
      current_s += replacementLength;
    }
    else {
      *current_s = *current_s_copy;
      current_s++;
    }
    current_s_copy++;
  }
  return s;
}


int main() {
  char input[256];
  strcpy(input, "Hello world, it's  a new day.");
  printf("Before: %s\n", input);
  URLify(input);
  printf("After : %s\n", input);
  return 0;
}