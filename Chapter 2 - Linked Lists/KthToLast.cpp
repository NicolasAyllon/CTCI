/* 
   Kth To Last:
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
// The kth-to-last-element is
// 

//                    kth       3rd    2nd   last
//                     |         |      |      |
// 0 -> 1 -> 2 -> ... N-k ...-> N-3 -> N-2 -> N-1

void detectErrors(SinglyLinkedList& list, int k);

// Preconditions:
// -list is not empty
// -k is a positive number not larger than the list size
// Throws an error otherwise
int KthToLast(SinglyLinkedList& list, int k) {
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
      std::cout << k << "-th to last: " << KthToLast(list, k) << '\n';
      std::cout << '\n';
    }
  }
}
