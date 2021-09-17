#include <iostream>
#include <sstream>
#include <exception>

template <typename T> class Queue;
template <typename T> std::ostream& operator<<(std::ostream&, const Queue<T>&);

template <typename T>
class Queue {
 private:
  struct Node {
    T data;
    Node* next;
    Node(T data_in = T(), Node* next_in = nullptr);
  };
  Node* front_;
  Node* back_;
  int size_;

 public:
  Queue();
  ~Queue();
  void CheckEmptyAndThrow() const;
  void enqueue(T data);
  void dequeue();
  const T& front() const;
  const T& back() const;
  bool empty() const;
  int size() const;
  std::string toString() const;
  friend std::ostream& operator<< <T>(std::ostream& out, const Queue<T>& queue);
};



template <typename T>
Queue<T>::Node::Node(T data_in, Node* next_in)
  : data(data_in), next(next_in) 
  {}

template <typename T>
Queue<T>::Queue() {
  front_ = nullptr;
  back_ = nullptr;
  size_ = 0;
}

template <typename T>
Queue<T>::~Queue() {
  Node* current = front_;
  while(current != nullptr) {
    Node* nodeToDelete = current;
    current = current->next;
    delete nodeToDelete;
  }
}

template <typename T>
void Queue<T>::CheckEmptyAndThrow() const {
  if(empty()) {
    throw std::logic_error("Queue is empty");
  }
}

template <typename T>
void Queue<T>::enqueue(T data) {
  if(front_ == nullptr) {
    front_ = new Node(data); // by default, next = nullptr
    back_ = front_;
    size_ = 1;
    return;
  }
  // Otherwise there is a last element,
  // so set its next pointing to it.
  Node* node = new Node(data);
  back_->next = node;
  back_ = node;
  size_++;
}

template <typename T>
void Queue<T>::dequeue() {
  // If the queue is empty, do nothing.
  if(empty()) return;
  // If only 1 item, 
  if(front_ == back_) {
    Node* nodeToDelete = front_;
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
    delete nodeToDelete;
    return;
  }
  // More than 1 item in queue:
  // Delete the node at the front of the queue and 
  // advance front_ to point to the node behind it.
  Node* nodeToDelete = front_;
  front_ = front_->next;
  delete nodeToDelete;
  size_--;
}

template <typename T>
const T& Queue<T>::front() const {
  CheckEmptyAndThrow();
  return front_->data;
}

template <typename T>
const T& Queue<T>::back() const {
  CheckEmptyAndThrow();
  return back_->data;
}

template <typename T>
bool Queue<T>::empty() const {
  return size_ == 0;
}

template <typename T>
int Queue<T>::size() const {
  return size_;
}

template <typename T>
std::string Queue<T>::toString() const {
  std::stringstream ss;
  ss << "front-> ";

  // If the queue isn't empty, insert items into stringstream
  if(front_ != nullptr) {
    // Insert 1st item
    ss << front_->data;  
    Node* current = front_->next;
    // Insert the rest
    while(current != nullptr) {
      ss << ", " << current->data;
      current = current->next;
    }
  }

  ss << " <-back";
  return ss.str();
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Queue<T>& queue) {
  out << queue.toString();
  return out;
}