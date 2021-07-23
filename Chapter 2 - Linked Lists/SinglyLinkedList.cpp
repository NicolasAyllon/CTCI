#include <iostream>

// DECLARATIONS
class SinglyLinkedList {
  private:
  struct Node {
    int data;
    Node* next;
    Node(int data = 0, Node* next = nullptr);
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
  Node* nodeAt(int index);
  Node* headNode();
  Node* tailNode();

  // Overload operator <<
  friend std::ostream& operator<<(
    std::ostream& out, const SinglyLinkedList& list);
  
  // For printing from node to end
  friend void printToEnd(Node* head);

  // Challenges
  friend void removeDups(SinglyLinkedList& list);

  friend int KthToLast_iterative(SinglyLinkedList& list, int k);
  friend int KthToLast_recursive(SinglyLinkedList& list, int k);
  friend Node* KthToLast_recursive_helper
      (SinglyLinkedList& list, Node*, int& k, int& i);

  friend void deleteMiddleNode(Node* node);

  friend void partition(SinglyLinkedList& list, int partition);
  friend bool isPartitioned(SinglyLinkedList& list, int partition);

  friend Node* sumLists(Node* head1, Node* head2);
  friend Node* sumLists_recursive(Node* head1, Node* head2);
  friend Node* sumLists_recursive(Node* head1, Node* head2, int carry);

};


// PRIVATE
// *******
// Default values (data = 0, next = nullptr)
SinglyLinkedList::Node::Node(int data, Node* next) {
  this->data = data;
  this->next = next;
}

// Return pointer to node at given 0-based index
// Returns nullptr if
// - the list is empty
// - index is negative or too large (beyond end of list)
SinglyLinkedList::Node* SinglyLinkedList::nodeAt(int index) {
  if(index < 0) return nullptr;

  SinglyLinkedList::Node* current = this->head;
  int i = 0;
  while(current != nullptr) {
    // If at correct index, return
    if(i == index) return current;
    // Otherwise advance current and increment i
    current = current->next;
    ++i;
  }
  return current; 
  // equal to nullptr 
  // if list is empty or we've reached the end of the list (index is too large)
}

SinglyLinkedList::Node* SinglyLinkedList::headNode() {
  return this->head;
}

SinglyLinkedList::Node* SinglyLinkedList::tailNode() {
  return this->tail;
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

// Prints a list from a starting node to the end
void printToEnd(SinglyLinkedList::Node* head) {
  if(head == nullptr) {
    std::cout << "->";
  }
  else {
    // Print 1st item
    std::cout << "-> " << head->data;
    // Print the rest 
    SinglyLinkedList::Node* current = head->next;
    while(current != nullptr) {
      std::cout << " -> " << current->data;
      current = current->next;
    }
  }
  std::cout << '\n';
}