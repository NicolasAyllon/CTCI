#include <iostream>
#include <sstream>
#include <exception>

template <typename T> class Stack;
template <typename T> std::ostream& operator<<(std::ostream&, const Stack<T>&);
template <typename T> void printVertically(const Stack<T>&);

// Declarations
template <typename T>
class Stack {
  private:
    struct Node {
      T data;
      Node* below;
      Node(T data_in = T(), Node* below_in = nullptr);
    };
    Node* top_;
    int size_;

  public:
    Stack();
    ~Stack();
    void push(T data);
    T top() const;
    void pop();
    bool empty() const;
    int size() const;
    std::string toString() const;

    friend std::ostream& operator<< <T>(std::ostream&, const Stack<T>&);
    friend void printVertically <T>(const Stack<T>&);
};


template <typename T>
Stack<T>::Node::Node(T data_in, Node* below_in)
  : data(data_in), below(below_in) {}

template <typename T>
Stack<T>::Stack() 
  :top_(nullptr), size_(0) {}

template <typename T>
Stack<T>::~Stack() {
  Node* current = top_;
  Node* nodeToDelete;
  while(current != nullptr) {
    nodeToDelete = current;
    current = current->below;
    delete nodeToDelete;
  }
}

template <typename T>
void Stack<T>::push(T data) {
  Node* node = new Node(data, top_);
  top_ = node;
  ++size_;
}

template <typename T>
T Stack<T>::top() const {
  if(top_ == nullptr) { throw std::logic_error("Stack is empty"); }
  return top_->data;
}

template <typename T>
void Stack<T>::pop() {
  if(top_ == nullptr) return;
  Node* nodeToDelete = top_;
  top_ = top_->below;
  delete nodeToDelete;
  --size_;
}

template <typename T>
bool Stack<T>::empty() const {
  return size_ == 0;
}

template <typename T>
int Stack<T>::size() const {
  return size_;
}

template <typename T>
std::string Stack<T>::toString() const {
  if(size_ == 0) {
    return "-> ";
  }
  // insert first item into stringstream
  std::stringstream ss;
  ss << "-> " << top_->data;
  // insert the rest
  Node* current = top_->below;
  while(current != nullptr) {
    ss << " -> " << current->data;
    current = current->below;
  }
  // return stringstream as string
  return ss.str();
}


// Overload operator <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const Stack<T>& stack) {
  out << stack.toString();
  return out;
}

// Print functions

template <typename T>
void printVertically(const Stack<T>& stack) {
  std::cout << "-> top" << '\n';
  auto current = stack.top_;
  while(current != nullptr) {
    std::cout << current->data << '\n';
    current = current->below;
  }
  std::cout << "-> bottom" << '\n';
}

// template <typename T>
// void printToEndDetailed(const Stack<T>& stack) {
//   printf("top: %x", top_);
//   Node* current = top_;
//   while(current != nullptr) {
//     printf("↓\n");
//     printf("current: %x", current);
//     std::cout << "data: " << current->data << '\n';
//     printf("below: %x", current->next);
//   }
//   std::cout << "―" << '\n';
// }
