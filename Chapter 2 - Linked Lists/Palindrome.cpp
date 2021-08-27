/* 
Palindrome:
Implement a function to check if a linked list is a palindrome.
*/
#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include "SinglyLinkedList.cpp"

struct SinglyLinkedListNode {
  int data;
  SinglyLinkedListNode* next;
  SinglyLinkedListNode
    (int data_in = 0, SinglyLinkedListNode* next_in = nullptr)
    : data(data_in), next(next_in) {};
};

bool isPalindrome(SinglyLinkedList::Node* head) {
  if(head == nullptr || head->next == nullptr) {
    return true;
  }
  SinglyLinkedList::Node* slow = head;
  SinglyLinkedList::Node* fast = head;
  std::stack<int> s;
  while(fast != nullptr && fast->next != nullptr) {
    s.push(slow->data);
    slow = slow->next;
    fast = fast->next->next;
  }
  /* After this loop:
     
     EVEN length list:
     fast == nullptr and slow points to the first item in the right half 
     of the list. No action necessary. 
     Ready to compare items in the right half with the stack's (s).
    
                    s                 f
                    ↓                 ↓
     1 -> 2 -> 3 -> 4 -> 5 -> 6 -> nullptr
     
     ODD length list:
     fast->next == nullptr (meaning fast != nullptr) and 
     slow points to the middle item in the list.
     Adavance one node, so slow points to the first item in the right half.
    
               s -> s    f
               ↓    ▼    ↓
     1 -> 2 -> 3 -> 4 -> 5 -> nullptr
  */
  if(fast != nullptr) {
    slow = slow->next;
  }
  while(slow != nullptr) {
    if(slow->data != s.top()) {
      return false;
    }
    slow = slow->next;
    s.pop();
  }
  return true;
}

int main() {
  std::ifstream testFile("Palindrome_test.txt");
  if(testFile.is_open()) {
    std::string s_list;
    while(std::getline(testFile, s_list)) {
    SinglyLinkedList list;
    std::stringstream ss_list(s_list);
    int data = 0;
    while(ss_list >> data) {
      list.push_back(data);
    }
    std::cout << list << '\n';
    std::string result = isPalindrome(list.headNode()) ? "true" : "false";
    std::cout << "Palindrome: " << result << '\n';
    std::cout << '\n';
    }
  }
}