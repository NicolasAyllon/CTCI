/* 
   K-th To Last:
   Implement an algorithm to find the kth to last element 
   of a singly linked list.
*/

#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include "SinglyLinkedList.cpp"

// In list with N items:
//
// 0 -> 1 -> 2 -> ... -> N-1
//
// The kth-to-last-element is at "index" N-k
// 
//                    kth       3rd    2nd   last
//                     |         |      |      |
// 0 -> 1 -> 2 -> ... N-k ...-> N-3 -> N-2 -> N-1

// Preconditions:
// -list is not empty
// -k is a positive number not larger than the list size
void detectErrors(SinglyLinkedList& list, int k);
// Throws an error otherwise


// Method 1: Counting
int KthToLast_count(SinglyLinkedList& list, int k) {
  detectErrors(list, k);
  SinglyLinkedList::Node* head = list.head;
  SinglyLinkedList::Node* current = head;

  for(int i = 0; i < list.size() - k; ++i) {
    current = current->next;
  }
  // Now current is at "index" N-k, the kth-to-last item
  // return data at this node
  return current->data;
}


// Method 2: Recursion
int KthToLast_recursive(SinglyLinkedList& list, int k) {
  SinglyLinkedList::Node* current = list.head;
  SinglyLinkedList::Node* result;
  int i = 0;
  result = KthToLast_recursive_helper(list, current, k, i);
  return result->data;
}

SinglyLinkedList::Node* KthToLast_recursive_helper
    (SinglyLinkedList& list, SinglyLinkedList::Node* current, int& k, int& i) {
  if(current == nullptr) {
    i = 0; // for clarity
    return nullptr;
  }
  else {
    // Recurse to end of list
    SinglyLinkedList::Node* result;
    result = KthToLast_recursive_helper(list, current->next, k, i);
    // Then increment i starting at 0 as calls are popped off the stack frame
    ++i;
    // Set result as current node at the desired element (kth-from-last)
    if(i == k) result = current;
    return result;
  }
}


void detectErrors(SinglyLinkedList& list, int k) {
  if(list.empty()) {
    throw std::invalid_argument("list cannot be empty");
  }
  if(k <= 0) {
    throw std::invalid_argument("value of k must be greater than 0");
  }
  if(k > list.size()) {
    throw std::invalid_argument("value of k cannot be greater than list size");
  }
}

// Read test data from file.
// Example input (2 lines):
// 2 7 1 8 2 9 1 8 3  <- space separated list
// 4                  <- value of k
//
// output:
// 9                  <- 4th-to-last item is 9
int main() {
  std::ifstream testFile("KthToLast_test.txt");
  if(testFile.is_open()) {
    
    std::string line_list;
    std::string line_k;

    while(std::getline(testFile, line_list)) {
      
      SinglyLinkedList list;
      std::stringstream ss(line_list);
      int data = 0;

      while(ss >> data) {
        list.push_back(data);
      }
      // Assume the following line contains k
      std::getline(testFile, line_k);
      int k = std::stoi(line_k);
      // Print list and k-th to last element on separate lines
      std::cout << list << '\n';
      std::cout << "calulated size: " << list.calculateSize() << '\n';
      std::cout << k << "-th to last: " << KthToLast_recursive(list, k) << '\n';
      std::cout << '\n';
    }
  }
}
