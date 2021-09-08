/*
Queue via Stacks:
Implement a class which implements a queue using two stacks.
*/

#include <exception>
#include <sstream>
#include <stack>

/* 
Approach:
Use one stack for holding enqueued items and another for holding items to
dequeue. Whenever the dequeue stack is empty, pop all items from the enqueue
stack and push them onto the dequeue stack, where they will be the correct
order to be dequeued.

Example:

    enqueue_stack_: 2, 3, 4, 5 <-top
    dequeue_stack_: 1 <-top

  After 1 is dequeued, dequeue_stack_ is empty, so transfer all elements from
  enqueue_stack_ to dequeue_stack_.

    enqueue_stack_: 2, 3, 4, 5 <-top
    dequeue_stack_: 
                ↓ transfer
    enqueue_stack_:
    dequeue_stack_: 5, 4, 3, 2 <-top

Notice that the back of the queue is usually at the top of enqueue_stack_, 
but not when enqueue_stack_ is empty. For that reason, just track the most 
recently enqueued element in a member variable, back_, and return it
for any call to back().
*/

template <typename T>
class Queue_Stack {
 private:
  std::stack<T> enqueue_stack_;
  std::stack<T> dequeue_stack_;
  int size_;
  T back_; // track the most recently

 public:
  Queue_Stack() : size_(0) {}

  // If dequeue stack is empty, 
  // pop all elements from enqueue stack 
  // onto dequeue stack.
  void TransferIfNecessary() {
    if(dequeue_stack_.empty()) {
      while(!enqueue_stack_.empty()) {
        dequeue_stack_.push(enqueue_stack_.top());
        enqueue_stack_.pop();
      }
    }
  }

  // Throws an error if the stack is empty, used where operations on an 
  // empty queue do not make sense, like dequeue(), front(), and back().
  void CheckEmptyAndThrow() const {
    if(empty()) {
      throw std::logic_error("Queue is empty");
    }
  }

  // Push the data onto the enqueue_stack_ and transfer it immediately to
  // dequeue_stack_ if the queue is currently empty. Cache data as back item.
  void enqueue(const T& data) {
    enqueue_stack_.push(data);
    TransferIfNecessary();
    back_ = data;
    ++size_;
  }

  // Dequeue item from dequeue_stack_. If the dequeue_stack_ is empty 
  // afterwards, transfer all items from enqueue_stack_ to dequeue_stack_.
  void dequeue() {
    CheckEmptyAndThrow();
    dequeue_stack_.pop();
    TransferIfNecessary();
    --size_;
  }

  // The oldest item in the queue (the back) is always at the top 
  // of dequeue_stack_ so return it.
  const T& front() const {
    CheckEmptyAndThrow();
    return dequeue_stack_.top();
  }

  // The item at the back of a non-empty queue is always the one 
  // most recently enqueued, which is stored in the member back_.
  const T& back() const {
    CheckEmptyAndThrow();
    return back_;
  }

  bool empty() const {
    return size_ == 0;
  }

  // std::stack doesn't have iterators, so printing of enqueue_stack 
  // and dequeue_stack is achieved by popping all elements onto a 
  // temporary stack and then pushing them back on the original stack.
  std::string toStringInternal() {
    std::stack<T> temp;
    std::stringstream ss;

    ss << "enqueue_stack: ";
    while(!enqueue_stack_.empty()) {
      temp.push(enqueue_stack_.top());
      enqueue_stack_.pop();
    }
    while(!temp.empty()) {
      ss << temp.top() << " ";
      enqueue_stack_.push(temp.top());
      temp.pop();
    }
    ss << "<-top\n";


    ss << "dequeue_stack: ";
    while(!dequeue_stack_.empty()) {
      temp.push(dequeue_stack_.top());
      dequeue_stack_.pop();
    }
    while(!temp.empty()) {
      ss << temp.top() << " ";
      dequeue_stack_.push(temp.top());
      temp.pop();
    }
    ss << "<-top\n";

    return ss.str();
  }
};