/* Remove Duplicates:
Write code to remove duplicates from an unsorted linked list.
FOLLOW UP
How would you solve this problem if a temporary buffer is not allowed?
*/
#include <iostream>
#include <fstream>
#include <sstream>

#include "SinglyLinkedList.cpp"
#include <unordered_set>

// With hash table (std::unordered_map)
void removeDups(SinglyLinkedList& list) {
  if(list.head == nullptr || list.head == list.tail) return;

  std::unordered_set<int> seen;
  seen.insert(list.head->data);
  SinglyLinkedList::Node* slow = list.head;
  SinglyLinkedList::Node* fast = list.head->next;

  while(fast != nullptr) {
    if(seen.find(fast->data) == seen.end()) {
      seen.insert(fast->data);
      slow = slow->next;
      fast = fast->next;
    }
    else {
      SinglyLinkedList::Node* duplicate = fast;
      slow->next = fast->next;
      fast = fast->next;
      delete duplicate;
    }
  }
  list.tail = slow;
}

int main() {
  std::ifstream testFile("RemoveDups_test.txt");
  if(testFile.is_open()) {
    std::string line;
    while(std::getline(testFile, line)) {
      SinglyLinkedList list;
      std::stringstream ss(line);
      
      int data;
      while(ss >> data) {
        list.push_back(data);
      }

      std::cout << "before: " << list << '\n';
      removeDups(list);
      std::cout << "after : " << list << '\n';
      std::cout << '\n';
    }
  }
}
