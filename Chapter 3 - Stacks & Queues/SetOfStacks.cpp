/*
Stack of Plates: 
Imagine a (literal) stack of plates. If the stack gets too high, 
it might topple. Therefore, in real life, we would likely start a new
stack when the previous stack exceeds some threshold.

Implement a data structure SetOfStacks that mimics this. SetOfStacks should
be composed of several stacks and should create a new stack once the
previous one exceeds capacity. SetOfStacks.push() and SetOfStacks.pop() 
should behave identically to a single stack (that is, pop() should return 
the same values as it would if there were just a single stack).

Follow up:
Implment a function popAt(int index) which performs a pop operation 
on a specific sub-stack.
*/
#include <exception>
#include <iostream>
#include <sstream>

template <typename T>
class FixedCapacitySubstack {
 private:

  T* array_;
  static const int k_capacity_ = 8;
  int size_;
  int top_idx_;

  //[?] Note: 
  //? Since the array is always of fixed size, future revisions can replace
  //? T* array_ = new T[k_capacity_];
  //? with
  //? T array_[k_capacity_];

 public:
  FixedCapacitySubstack() {
    std::cout << "FixedCapacitySubstack constructor called!\n";
    array_ = new T[k_capacity_]{};
    size_ = 0;
    top_idx_ = -1;
  }

  ~FixedCapacitySubstack() {
    std::cout << "FixedCapacitySubstack destructor called" << '\n';
    delete[] array_;
  }

  void CheckEmptyAndThrow() {
    if(empty()) {
      throw std::logic_error("Stack is empty");
    }
  }

  // Returns a bool depending on whether the push was successful
  bool push(T data) {
    if(size_ == k_capacity_) {
      return false;
    }
    array_[++top_idx_] = data;
    ++size_;
    return true;
  }

  T top() {
    CheckEmptyAndThrow();
    return array_[top_idx_];
  }

  void pop() {
    CheckEmptyAndThrow();
    array_[top_idx_] = 0; // for visualization only
    --top_idx_;
    --size_;
  }

  bool empty() {
    return size_ == 0;
  }

  bool full() {
    return size_ == k_capacity_;
  }

  std::string toString() {
    if(empty()) {
      return "[]";
    }
    std::stringstream ss;
    // Insert 1st item in stream
    ss << "[" << array_[0];
    for(int i = 1; i <= top_idx_; ++i) {
      ss << ", " << array_[i];
    }
    ss << "]";
    return ss.str();
  }

  std::string toStringInternal() {
    std::stringstream ss;
    // Insert 1st item in stream
    ss << "[" << array_[0];
    for(int i = 1; i < k_capacity_; ++i) {
      ss << ", " << array_[i];
    }
    ss << "]";
    return ss.str();
  }
};



template <typename T>
class SetOfStacks {
 private:
  FixedCapacitySubstack<T>** substack_array_;
  static const int k_default_capacity_ = 4;
  static const int k_min_capacity_ = 4;
  int capacity_;
  int top_substack_idx_;
  int num_substacks_;

  // get
  const FixedCapacitySubstack<T>*& topSubstack() const {
    return substack_array_[top_substack_idx_];
  }

  // set
  FixedCapacitySubstack<T>*& topSubstack() {
    return substack_array_[top_substack_idx_];
  }

 public:
  SetOfStacks() {
    substack_array_ = new FixedCapacitySubstack<T>* [k_default_capacity_]{};
    capacity_ = k_default_capacity_;

    substack_array_[0] = new FixedCapacitySubstack<T>();
    top_substack_idx_ = 0;
    num_substacks_ = 1;
  }

  ~SetOfStacks() {
    std::cout << "SetOfStacks destructor called" << '\n';
    for(int i = 0; i <= top_substack_idx_; i++) {
      delete substack_array_[i];
    }
    delete[] substack_array_;
  }

  void Resize(int new_capacity) {
    FixedCapacitySubstack<T>** old = substack_array_;
    substack_array_ = new FixedCapacitySubstack<T>* [new_capacity]{};
    // On failed allocation reset substack_array_ back to old, and return
    if(substack_array_ == nullptr) {
      substack_array_ = old;
      return;
    }
    // Copy values at indices holding pointers to nonempty substacks
    for(int i = 0; i <= top_substack_idx_; ++i) {
      substack_array_[i] = old[i];
    }
    delete[] old;
    // Line below only for testing
    std::cout << "Resized substack array from " << capacity_
              << " to " << new_capacity << '\n';
    capacity_ = new_capacity;
  }

  void ResizeSubstackArrayIfNecessaryOnPush() {
    if(num_substacks_ == capacity_) {
      if(topSubstack()->full()) {
        Resize(2*capacity_);
      }
    }
  }

  void ResizeSubstackArrayIfNecessaryOnPop() {
    if(num_substacks_ < capacity_/4) {
      if(capacity_ > k_min_capacity_) {
        Resize(capacity_/2);
      }
    }
  }

  void push(T data) {
    ResizeSubstackArrayIfNecessaryOnPush();
    if(topSubstack()->full()) {
      ++top_substack_idx_;
      ++num_substacks_;
      substack_array_[top_substack_idx_] = new FixedCapacitySubstack<T>();
    }
    topSubstack()->push(data);
  }

  T top() {
    return topSubstack()->top();
  }

  void pop() {
    topSubstack()->pop();
    if(topSubstack()->empty() && num_substacks_ > 1) {
      delete substack_array_[top_substack_idx_];
      substack_array_[top_substack_idx_] = nullptr; 
      // set back to nullptr so toStringInternal() can print
      --top_substack_idx_;
      --num_substacks_;
    }
    ResizeSubstackArrayIfNecessaryOnPop();
  }

  // Follow up:
  // Implment a function popAt(int index) whic performs a pop operation 
  // on a specific sub-stack.
  void popAt(int index) {
    // If out of bounds, do nothing
    if(index < 0 || top_substack_idx_< index) {
      return;
    }
    substack_array_[index]->pop();
  }

  bool empty() {
    return num_substacks_ == 1 && topSubstack()->empty();
  }

  std::string toString() {
    std::stringstream ss;
    for(int i = 0; i <=top_substack_idx_; ++i) {
      ss << substack_array_[i]->toString() << '\n';
    }
    return ss.str();
  }

  std::string toStringInternal() {
    std::stringstream ss;
    for(int i = 0; i < capacity_; ++i) {
      ss << substack_array_[i] << ": ";

      if(substack_array_[i] != nullptr) {
        ss << substack_array_[i]->toStringInternal();
        if(i == top_substack_idx_) {
          ss << "<- top";
        }
        ss << '\n';
      }

      else {
        ss << "(null)" << '\n';
      }
    }
    return ss.str();
  }
};
