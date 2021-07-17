/*
Delete Middle Node:
Implement an algorithm to delete a node in the middle 
(any node other than the first or last, not necessary the exact middle) 
of a singly linked list, given only access to that node.
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SinglyLinkedList.cpp"


// Precondition: 
// node points a node that is not the first or last in the list
void deleteMiddleNode(SinglyLinkedList::Node* node) {
  // If the node is null or at the end of the list, do nothing
  if(node == nullptr || node->next == nullptr) return;
  // copy data from next node 
  SinglyLinkedList::Node* nextNode = node->next;
  node->data = nextNode->data;
  node->next = nextNode->next;
  delete nextNode;
  // delete and the next node
}

int main () {
  std::ifstream testFile("DeleteMiddleNode_test.txt");
  if(testFile.is_open()) {

    std::string s_list;
    std::string s_nodeIndex;

    while(std::getline(testFile, s_list)) {
      // Read 1st line containing list
      SinglyLinkedList list;
      std::stringstream ss_list(s_list);
      int data = 0;
      // push data into list
      while(ss_list >> data) {
        list.push_back(data);
      }
      // Read 2nd line containing index to delete
      std::getline(testFile, s_nodeIndex);
      int indexToDelete = std::stoi(s_nodeIndex);
      // Print before and after
      std::cout << "before: " << list << '\n';
      deleteMiddleNode(list.nodeAt(indexToDelete));
      std::cout << "deleted node at index " << indexToDelete << '\n';
      std::cout << "after:" << list << '\n';
      std::cout << '\n';
    }
  }
}