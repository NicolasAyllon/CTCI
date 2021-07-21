/*
Sum Lists:
You have two numbers represented by a linked list, where each node contains 
a single digit. The digits are stored in reverse order, such that the 1's digit
is at the head of the list. Write a function that adds the wtwo numbers and
returns the sum as linked list.
Example:
Input: (7 -> 1 -> 6) + (5 -> 9 -> 2). That is, 617 + 296.
Output: 2 -> 1 -> 9. That is, 912.
*/

#include <iostream>
#include <string>
#include <list>
//#include "SinglyLinkedList.cpp"

using list = std::list<int>;

list sumLists(const list& l1, const list& l2) {
  list result;
  // If either list is empty, copy the other into result and return it.
  if(l1.empty()) {
    result = l2;
    return result;
  }
  if(l2.empty()) {
    result = l1;
    return result;
  }

  // Both lists are non-empty so begin addition
  int digit1 = 0;
  int digit2 = 0;
  int digitSum = 0;
  int res_digit = 0;
  int carry = 0;

  list::const_iterator it1 = l1.begin();
  list::const_iterator it2 = l2.begin();
  
  while(it1 != l1.end() || it2 != l2.end()) {
    // get digits, returning 0's for past the end of the list
    digit1 = (it1 != l1.end() ? *it1 : 0);
    digit2 = (it2 != l2.end() ? *it2 : 0);
    // calculate resulting digit and carry
    digitSum = digit1 + digit2 + carry;
    res_digit = digitSum % 10;
    carry = digitSum / 10;
    // push digit to back of result, advance iterators
    result.push_back(res_digit);
    // advance iterators if not already at end
    if(it1 != l1.end()) ++it1;
    if(it2 != l2.end()) ++it2;
  }
  // If there is nonzero carry after reaching the end of both lists, 
  // push it onto the result as the final digit.
  if(carry != 0) {
    result.push_back(carry);
  }
  return result;
}

// Print function to use in main()
void print(const list& l) {
  for(int val : l) { std::cout << val << " "; }
  std::cout << '\n';
}

int main() {
  // Test hardcoded lists
  list testList1;
  testList1.push_back(9);
  testList1.push_back(9);
  testList1.push_back(9);
  list testList2;
  testList2.push_back(1);
  // testList2.push_back(0);
  // testList2.push_back(0);

  print(testList1);
  print(testList2);
  print(sumLists(testList1, testList2));
}