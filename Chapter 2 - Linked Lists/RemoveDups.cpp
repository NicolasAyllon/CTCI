/* Remove Duplicates:
Write code to remove duplicates from an unsorted linked list.
FOLLOW UP
How would you solve this problem if a temporary buffer is not allowed?
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>

struct Node {
  int data;
  Node* next;

  Node(int data = 0) {
    this->data = data;
    this->next = nullptr; // Try adding this next
  }
};

class SinglyLinkedList {
  private:
  Node* head;
  Node* tail;
  
  public:
  SinglyLinkedList() {
    head = nullptr;
    tail = nullptr;
  }

  ~SinglyLinkedList() {
    Node* current = head;
    Node* nodeToDelete;
    while(current != nullptr) {
      nodeToDelete = current;
      current = current->next;
      //std::cout << "deleting node at " << nodeToDelete << '\n';
      delete nodeToDelete;
    }
  }

  void push_back(int data) {
    Node* node = new Node(data);
    // List is empty, set head and tail pointing to new node
    if(head == nullptr) {
      head = node;
      tail = node;
      return;
    }
    // List not empty, set tail to point to new node, then update tail
    tail->next = node;
    tail = node;
  }

  void pop_back() {
    // 0-item list
    if(tail == nullptr) return;
    // 1-item list
    if(tail == head) {
      delete tail;
      head = nullptr;
      tail = nullptr;
      return;
    }
    // multiple item list
    Node* current = head;
    while(current->next != tail) {
      current = current->next;
    }
    // now current->next = tail
    delete tail;
    tail = current;
    tail->next = nullptr;
  }

  // With hash table (std::unordered_map)
  void removeDups() {
    if(head == nullptr || head == tail) return;

    std::unordered_set<int> seen;
    seen.insert(head->data);
    Node* slow = head;
    Node* fast = head->next;

    while(fast != nullptr) {
      if(seen.find(fast->data) == seen.end()) {
        seen.insert(fast->data);
        slow = slow->next;
        fast = fast->next;
      }
      else {
        Node* duplicate = fast;
        slow->next = fast->next;
        fast = fast->next;
        delete duplicate;
      }
    }
    tail = slow;
  }

  // Overload << must be defined outside of class 
  // because LHS is not of type SinglyLinkedList
  friend std::ostream& operator<<(
      std::ostream& out, const SinglyLinkedList& list);

};
// Overload <<
std::ostream& operator<<(std::ostream& out, const SinglyLinkedList& list) {
  if(list.head == nullptr) {
    std::cout << "->";
  } 
  else {
    // Print 1st item
    std::cout << "-> " << list.head->data;
    // Print the rest
    Node* current = list.head->next;
    while(current != nullptr) {
      std::cout << " -> " << current->data;
      current = current->next;
    }
  }
  return out;
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
      list.removeDups();
      std::cout << "after : " << list << '\n';
      std::cout << '\n';
    }
  }
}
