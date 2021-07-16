#include <iostream>

// DECLARATIONS
class SinglyLinkedList {
  private:
  struct Node {
    int data;
    Node* next;
    Node(int data = 0);
  };
  Node* head;
  Node* tail;
  int m_size;

  public:
  SinglyLinkedList();
  ~SinglyLinkedList();
  bool empty();
  int size();
  int calculateSize();
  void push_back(int item);
  void pop_back();

  // Overload operator <<
  friend std::ostream& operator<<(
    std::ostream& out, const SinglyLinkedList& list);
  
  // Challenges
  friend void removeDups(SinglyLinkedList& list);
  friend int KthToLast(SinglyLinkedList& list, int k);
};


// PRIVATE
// *******
SinglyLinkedList::Node::Node(int data) {
  this->data = data;
  this->next = nullptr;
}

// PUBLIC
// ******
SinglyLinkedList::SinglyLinkedList() {
  head = nullptr;
  tail = nullptr;
  m_size = 0;
}

SinglyLinkedList::~SinglyLinkedList() {
  Node* current = head;
  Node* nodeToDelete;
  while(current != nullptr) {
    nodeToDelete = current;
    current = current->next;
    //std::cout << "deleting node at " << nodeToDelete << '\n';
    delete nodeToDelete;
  }
}

bool SinglyLinkedList::empty() {
  return m_size == 0;
}

int SinglyLinkedList::size() {
  return m_size;
}

// A verification method that counts the number of elements in O(n) time.
int SinglyLinkedList::calculateSize() {
  // For empty list, immediately return 0
  if(head == nullptr) return 0;
  // Otherwise traverse list and count elements
  int count = 0;
  Node* current = head;
  while(current != nullptr) {
    ++count;
    current = current->next;
  }
  return count;
}

void SinglyLinkedList::push_back(int data) {
  Node* node = new Node(data);
  // List is empty, set head and tail pointing to new node
  if(head == nullptr) {
    head = node;
    tail = node;
    ++m_size;
    return;
  }
  // List not empty, set tail to point to new node, then update tail
  tail->next = node;
  tail = node;
  ++m_size;
}

void SinglyLinkedList::pop_back() {
  // 0-item list
  if(tail == nullptr) return;
  // 1-item list
  if(tail == head) {
    delete tail;
    head = nullptr;
    tail = nullptr;
    m_size = 0;
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
  --m_size;
}



// Overload <<
std::ostream& operator<<(std::ostream& out, const SinglyLinkedList& list) {
  if(list.head == nullptr) {
    std::cout << "->";
  } 
  else {
    // Print 1st item
    std::cout << "-> " << list.head->data;
    // Print the rest
    SinglyLinkedList::Node* current = list.head->next;
    while(current != nullptr) {
      std::cout << " -> " << current->data;
      current = current->next;
    }
  }
  return out;
}