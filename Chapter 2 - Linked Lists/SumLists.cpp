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
#include "SinglyLinkedList.cpp"

using list = std::list<int>;

// Solution 1:
// Lists have the 1's digit at the head/front
// Using std::list;
list sumLists_stl(const list& l1, const list& l2) {
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

  // Both lists are non-empty
  // initialize values and iterators
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



// Solution 2:
// Lists have the 1's digit at the head
// Using SinglyLinkedList.cpp
SinglyLinkedList::Node* sumLists
    (SinglyLinkedList::Node* head1, SinglyLinkedList::Node* head2) {
  // Initializations
  SinglyLinkedList::Node* current1 = head1;
  SinglyLinkedList::Node* current2 = head2;
  SinglyLinkedList::Node* result_head = nullptr;
  SinglyLinkedList::Node* result_current = nullptr;
  int digit1 = 0;
  int digit2 = 0;
  int digitSum = 0;
  int resultDigit = 0;
  int carry = 0;
  // Iterate through list
  while(current1 != nullptr || current2 != nullptr) {
    digit1 = (current1 != nullptr ? current1->data : 0);
    digit2 = (current2 != nullptr ? current2->data : 0);

    digitSum = carry + digit1 + digit2;
    resultDigit = digitSum % 10;
    carry = digitSum / 10;

    // Create new node for this digit
    SinglyLinkedList::Node* node = new SinglyLinkedList::Node(resultDigit);

    // Add to the result list
    if(result_current == nullptr) {
      result_head = node; // also sets result_current = node
      result_current = node;
    } else {
      result_current->next = node;
      result_current = node;
    }
    // Advance current pointers
    if(current1 != nullptr) current1 = current1->next;
    if(current2 != nullptr) current2 = current2->next;
  }
  // If there's a carry after reaching the end of both lists, 
  // add it to the result list
  if(carry > 0) {
    SinglyLinkedList::Node* node = new SinglyLinkedList::Node(carry);
    result_current->next = node;
    result_current = node; // not necessary, but just for consistency, advance
  }
  return result_head;
}


// Print function to use in main()
void print(const list& l) {
  for(int val : l) { std::cout << val << " "; }
  std::cout << '\n';
}

int main() {
  // Test hardcoded lists
  // list testList1;
  // testList1.push_back(9);
  // testList1.push_back(9);
  // testList1.push_back(9);
  // list testList2;
  // testList2.push_back(1);
  // testList2.push_back(0);
  // testList2.push_back(0);
  // print(testList1);
  // print(testList2);
  // print(sumLists_stl(testList1, testList2));

  // 7 -> 1 -> 6 represents 617
  SinglyLinkedList testSLL1;
  testSLL1.push_back(7);
  testSLL1.push_back(1);
  testSLL1.push_back(6);

  // 5 -> 9 -> 2 represents 295
  SinglyLinkedList testSLL2;
  testSLL2.push_back(5);
  testSLL2.push_back(9);
  testSLL2.push_back(2);

  printToEnd(sumLists(testSLL1.headNode(), testSLL2.headNode()));
}