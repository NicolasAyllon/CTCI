/* Partition:
Write code to partition a linked list around a value x, such that all nodes
less than x come before all nodes greater than or equal to x. 
If x is contained within the list, the values of x only need to be after 
the elements less than x. The partition element x can appear anywhere in the
right partition. It does not need to appear between the left and right
partitions.

Example:
Input: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition = 5]
Output: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include "SinglyLinkedList.cpp"

// Using own implementation
void partition(SinglyLinkedList& list, int partition) {
  // If the list has 0 or 1 nodes, do nothing
  if(list.head == nullptr || list.head->next == nullptr) return;

  // Otherwise, create current, head & tails for left & right partitions
  SinglyLinkedList::Node* current = list.head;
  SinglyLinkedList::Node* left_head = nullptr;
  SinglyLinkedList::Node* left_tail = nullptr;
  SinglyLinkedList::Node* right_head = nullptr;
  SinglyLinkedList::Node* right_tail = nullptr;

  // Build left and right partitions
  while(current != nullptr) {
    if(current->data < partition) {
      if(left_head == nullptr) {
        left_head = left_tail = current;
      } else {
        left_tail->next = current;
        left_tail = current;
      }
    }
    // current->data >= partition
    else {
      if(right_head == nullptr) {
        right_head = right_tail = current;
      } else {
        right_tail->next = current;
        right_tail = current;
      }
    }
    current = current->next;
  }
  // Connect the partitions if left is non empty
  if(left_tail != nullptr && right_head != nullptr) {
    left_tail->next = right_head;
    // terminate list at right tail if previously in middle
    right_tail->next = nullptr; 
    list.head = left_head;
    list.tail = right_tail;
  }
}


// Utility to check if SinglyLinkedList is partitioned by value 'partition'
bool isPartitioned(SinglyLinkedList& list, int partition) {
  // A list with 0 or 1 elements is partitioned by vacuous truth
  if(list.head == nullptr || list.head->next == nullptr) return true;
  
  SinglyLinkedList::Node* current = list.head;
  bool inRightPartition = false;

  while(current != nullptr) {
    if(!inRightPartition) {
      if(current->data >= partition) 
        inRightPartition = true;
    } 
    // inRightPartition
    else {
      if(current->data < partition)
        return false;
    }
    current = current->next;
  }
  return true;
}


// Using std::list
void partition_stl(std::list<int>& list, int partition) {
  // implement
  std::list<int> rightPartition;
  auto it = list.begin();
  while(it != list.end()) {
    if(*it >= partition) {
      // After splicing an element pointed by iterator from list 1 into list 2,
      // the iterator now iterates throught list 2.
      // To avoid this and keep it iterating through the original list, 
      // make a copy of iterator it (called it_splice) 
      // and increment iterator it before splicing.
      auto it_splice = it; 
      ++it;
      rightPartition.splice(rightPartition.end(), list, it_splice);
    }
    else {
      ++it;
    }
  }
  list.splice(list.end(), rightPartition);
  return;
}


int main () {
  std::ifstream testFile("Partition_test.txt");
  if(testFile.is_open()) {
    std::string s_list;
    std::string s_partitionValue;
    while(std::getline(testFile, s_list)) {
      //SinglyLinkedList list;
      std::list<int> stl_list;
      std::stringstream ss_list(s_list);
      int data = 0;
      while(ss_list >> data) {
        //list.push_back(data);
        stl_list.push_back(data);
      }
      std::getline(testFile, s_partitionValue);
      int partitionValue = std::stoi(s_partitionValue);
      std::string result ="";

      //std::cout << "before: " << list << '\n';
      std::cout << "before: ";
      for(auto val: stl_list) {
        std::cout << val << " ";
      }
      std::cout << '\n';

      std::cout << "partition value: " << partitionValue << '\n';

      //result = isPartitioned(list, partitionValue) ? "true" : "false";
      //std::cout << "is partitioned: " << result << '\n';

      //partition(list, partitionValue);
      partition_stl(stl_list, partitionValue);
      //std::cout << "after: " << list << '\n';
      std::cout << "after: ";
      for(auto val: stl_list) {
        std::cout << val << " ";
      }
      std::cout << '\n';
      //result = isPartitioned(list, partitionValue) ? "true" : "false";
      //std::cout << "is partitioned: " << result << '\n';
      std::cout << '\n';
    }
  }
}
