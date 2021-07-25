/*
Sum Lists:
You have two numbers represented by a linked list, where each node contains 
a single digit. The digits are stored in reverse order, such that the 1's digit
is at the head of the list. Write a function that adds the wtwo numbers and
returns the sum as linked list.
Example:
Input: (7 -> 1 -> 6) + (5 -> 9 -> 2). That is, 617 + 295.
Output: 2 -> 1 -> 9. That is, 912.
*/

#include <iostream>
#include <fstream>
#include <sstream>
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

// Solution 3:
// Recursion with SinglyLinkedList
SinglyLinkedList::Node* sumLists_recursive
    (SinglyLinkedList::Node* head1, SinglyLinkedList::Node* head2) {
  int carry = 0;
  return sumLists_recursive(head1, head2, carry);
}

// Helping method
SinglyLinkedList::Node* sumLists_recursive
    (SinglyLinkedList::Node* head1, SinglyLinkedList::Node* head2, int carry) {
  // base case
  if(head1 == nullptr && head2 == nullptr && carry == 0) return nullptr;
  // get digits from non-null pointers
  int digit1 = (head1 != nullptr ? head1->data : 0);
  int digit2 = (head2 != nullptr ? head2->data : 0);
  // calculate this digit and increment the head of the next list by carry
  int sumDigits = digit1 + digit2 + carry;
  int resultDigit = sumDigits % 10;
  carry = sumDigits / 10;
  // Advance non-null pointers and make recursive call for head of the list
  // representing the rest of the sum.
  SinglyLinkedList::Node* newNode = new SinglyLinkedList::Node(resultDigit);
  if(head1 != nullptr) head1 = head1->next;
  if(head2 != nullptr) head2 = head2->next;
  newNode->next = sumLists_recursive(head1, head2, carry);
  return newNode;
}

// Convert to int to Linked List with the option (bool) of 1's digit as head
// 123 => 3->2->1
SinglyLinkedList intToList(int num, bool headIsOnesDigit = true) {
  SinglyLinkedList resultList;
  if(num == 0) {
    if(headIsOnesDigit) resultList.push_back(0);
    else resultList.push_front(0);
    return resultList;
  }
  while(num != 0) {
    int digit = num % 10;
    num /= 10;
    if(headIsOnesDigit) resultList.push_back(digit);
    else resultList.push_front(digit);
  }
  return resultList;
}

// Convenience function that forwards to intToList with headIsOnesDigit = false
// 123 => 1->2->3
SinglyLinkedList intToListReverse(int num) {
  return intToList(num, false);
}

// Solution 4:
// FOLLOW UP
// Return a list representing the sum in reverse (with 1's digit as tail)
// Example:
// Input: (6 -> 1 -> 7) + (2 -> 9 -> 5). That is, 617 + 295.
// Output: 9 -> 1 -> 2. That is, 912.
SinglyLinkedList::Node* sumListsReverse
    (SinglyLinkedList::Node* head1, SinglyLinkedList::Node* head2) {
  padZerosToEqualizeLength(head1, head2);
  int carry = 0;
  SinglyLinkedList::Node* alignedResult = sumListsReverse(head1, head2, carry);
  if(carry > 0) {
    return new SinglyLinkedList::Node(carry, alignedResult);
  } 
  else {
    return alignedResult;
  };
}
// Helper function
SinglyLinkedList::Node* sumListsReverse
    (SinglyLinkedList::Node* head1, SinglyLinkedList::Node* head2, int& carry) {
  // base case
  if(head1 == nullptr && head2 == nullptr) {
    return nullptr;
  }
  // Otherwise
  // First find result for the list that follows the head
  SinglyLinkedList::Node* next1 = (head1 != nullptr ? head1->next : nullptr);
  SinglyLinkedList::Node* next2 = (head2 != nullptr ? head2->next : nullptr);
  SinglyLinkedList::Node* result_rest = sumListsReverse(next1, next2, carry);
  // Calculate the resulting digit and carry
  int digit1 = (head1 != nullptr ? head1->data : 0);
  int digit2 = (head2 != nullptr ? head2->data : 0);
  int sumDigits = digit1 + digit2 + carry;
  int resultDigit = sumDigits % 10;
  carry = sumDigits / 10; 
  // Carry is passed by reference (int&), so changes higher in the call stack
  // (up to the 1's place at the end) are seen lower in the call stack
  return new SinglyLinkedList::Node(resultDigit, result_rest);
  // Create node to represent new digit in the result
  // pointing to head of the rest of the list (result_rest)
}

void padZerosToEqualizeLength
  (SinglyLinkedList::Node*& head1, SinglyLinkedList::Node*& head2) {
    SinglyLinkedList::Node* current1 = head1;
    SinglyLinkedList::Node* current2 = head2;
    while(current1 != nullptr || current2 != nullptr) {
      if(current1 == nullptr) {
        SinglyLinkedList::Node* node = new SinglyLinkedList::Node(0);
        node->next = head1;
        head1 = node;
      }
      if(current2 == nullptr) {
        SinglyLinkedList::Node* node = new SinglyLinkedList::Node(0);
        node->next = head2;
        head2 = node;
      }
      if(current1 != nullptr) current1 = current1->next;
      if(current2 != nullptr) current2 = current2->next;
    }
}

// Print function for std::list to use in main()
void print(const list& l) {
  for(int val : l) { std::cout << val << " "; }
  std::cout << '\n';
}

int main() {
  // Test lists from file
  std::ifstream testFile("SumLists_test.txt");
  if(testFile.is_open()) {
    std::string line;
    int num1, num2;
    while(std::getline(testFile, line)) {
      std::stringstream ss(line);
      ss >> num1 >> num2;
      // SinglyLinkedList l1 = intToList(num1);
      // SinglyLinkedList l2 = intToList(num2);
      SinglyLinkedList l1_reverse = intToListReverse(num1);
      SinglyLinkedList l2_reverse = intToListReverse(num2);
      // std::cout << "l1: ";
      // printToEnd(l1.headNode());
      // std::cout << "l2: ";
      // printToEnd(l2.headNode());
      // std::cout << "sumLists: ";
      // printToEnd(sumLists(l1.headNode(), l2.headNode()));
      // std::cout << "sumLists_recursive: ";
      // printToEnd(sumLists_recursive(l1.headNode(), l2.headNode()));
      // std::cout << '\n';
      std::cout << "l1_reverse: ";
      printToEnd(l1_reverse.headNode());
      std::cout << "l2_reverse: ";
      printToEnd(l2_reverse.headNode());
      printToEnd(sumListsReverse(l1_reverse.headNode(), l2_reverse.headNode()));
      std::cout << '\n'; 
    }
  }


  // // Test hardcoded std::lists
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


  // // Test sumLists and sumLists_recursive
  // // 7 -> 1 -> 6 represents 617
  // SinglyLinkedList testSLL1;
  // testSLL1.push_back(9);
  // testSLL1.push_back(9);
  // testSLL1.push_back(9);

  // // 5 -> 9 -> 2 represents 295
  // SinglyLinkedList testSLL2;
  // testSLL2.push_back(1);
  // // testSLL2.push_back(9);
  // // testSLL2.push_back(2);

  // std::cout << "sumLists: " << '\n';
  // printToEnd(sumLists(testSLL1.headNode(), testSLL2.headNode()));
  // std::cout << "sumLists_recursive: " << '\n';
  // printToEnd(sumLists_recursive(testSLL1.headNode(), testSLL2.headNode()));
}