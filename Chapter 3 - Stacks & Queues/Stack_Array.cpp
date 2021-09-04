/* 
Stack_Array is an implementation of the stack data structure using an array 
as the underlying type.

It is a more general version of exercise 3.1 in Cracking the Coding Interview, 
"Three in One", which asks how to use a single array to implement 3 stacks.
*/

#include <sstream>

template <typename T>
class Stack_Array {
 private:
  T* array_;
  static const int k_default_capacity = 16;
  static const int k_min_capacity = 8;
  int capacity_;
  int size_;
  int top_idx_;
  void Resize(int new_capacity);
  void ResizeIfNecessaryOnPush();
  void ResizeIfNecessaryOnPop();
  void CheckForEmptyAndThrow() const;

 public:
  Stack_Array();
  ~Stack_Array();
  void push(T data);
  T top() const;
  void pop();
  bool empty() const;
  int size() const;
  int capacity() const;

  std::string toString() const;
  std::string toStringInternal() const;
};

template <typename T>
Stack_Array<T>::Stack_Array() {
  array_ = new T[k_default_capacity]{};
  capacity_ = k_default_capacity;
  size_ = 0;
  top_idx_ = -1;
}

template <typename T>
Stack_Array<T>::~Stack_Array() {
  delete[] array_;
}

template <typename T>
void Stack_Array<T>::Resize(int new_capacity) {
  T* old = array_;
  array_ = new T[new_capacity]{};
  // On failed allocation, reset to old array with contents unchanged.
  if(array_ == nullptr) {
    array_ = old;
    return;
  }
  // Copy elements from old array into new one
  for(int i = 0; i < size_; ++i) {
    array_[i] = old[i];
  }
  // Then delete the old array & update capacity
  delete[] old;
  capacity_ = new_capacity;
}

template <typename T>
void Stack_Array<T>::ResizeIfNecessaryOnPush() {
  // If array is full, double the capacity
  if(size_ == capacity_) {
    Resize(2*capacity_);
  }
}

template <typename T>
void Stack_Array<T>::ResizeIfNecessaryOnPop() {
  // If array is larger than minimum capacity and less than a quarter full
  // halve the capacity
  if(capacity_ > k_min_capacity && size_ < capacity_/4) {
    Resize(capacity_/2);
  }
}

template <typename T>
void Stack_Array<T>::CheckForEmptyAndThrow() const {
  if(empty()) {
    throw std::logic_error("Stack is empty");
  }
}

template <typename T>
void Stack_Array<T>::push(T data) {
  ResizeIfNecessaryOnPush();
  array_[++top_idx_] = data;
  size_++;
}


template <typename T>
T Stack_Array<T>::top() const {
  CheckForEmptyAndThrow();
  return array_[top_idx_];
}

template <typename T>
void Stack_Array<T>::pop() {
  --top_idx_;
  --size_;
  ResizeIfNecessaryOnPop();
}

template <typename T>
bool Stack_Array<T>::empty() const {
  return size_ == 0;
}

template <typename T>
int Stack_Array<T>::size() const {
  return size_;
}

template <typename T>
int Stack_Array<T>::capacity() const {
  return capacity_;
}

template <typename T>
std::string Stack_Array<T>::toString() const {
  if(empty()) {
    return "[]";
  }
  std::stringstream ss;
  // Insert 1st item in stream
  ss << "[" << array_[0];
  // Insert the rest
  for(int i = 1; i < size_; ++i) {
    ss << ", " << array_[i];
  }
  ss << "]";
  return ss.str();
}

template <typename T>
std::string Stack_Array<T>::toStringInternal() const {
  std::stringstream ss;
  // Insert 1st item in stream
  ss << "[" << array_[0];
  // Insert the rest, showing the whole capacity of the internal array
  for(int i = 1; i < capacity_; ++i) {
    ss << ", " << array_[i];
  }
  ss << "]";
  return ss.str();
}

