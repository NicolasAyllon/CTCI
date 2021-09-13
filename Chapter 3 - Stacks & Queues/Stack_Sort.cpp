/*
Stack Sort:
Write a program to sort a stack such that the smallest items are on the top.
You can use an additional temporary stack, but you may not copy the 
elements into any other data structure (such as an array). The stack 
supports the following operations: push, pop, peek/top, and isEmpty.
*/

#include <iostream>
#include <sstream>
#include <stack>

// Forward declare print methods
template <typename T> std::string toString(std::stack<T>);
template <typename T> std::string toStringRecursive(std::stack<T> s);
template <typename T> std::string toStringRecursive(std::stack<T>& s, int);


template <typename T>
void SortStack(std::stack<T>& stack) {
  std::stack<T> temp;
  T cache;
  while(!stack.empty()) {
    if(temp.empty() || stack.top() >= temp.top()) {
      temp.push(stack.top());
      stack.pop();
      continue;
    }
    // The next item in the stack (top) is less than previous (at top of temp)
    // which means this element is out of order.
    // Save to cache and put back in order.
    cache = stack.top();
    stack.pop();
    
    while(!temp.empty() && cache < temp.top()) {
      stack.push(temp.top());
      temp.pop();
    }
    stack.push(cache);
  }
  // All items transfered from stack to temp and no out-of-order items found.
  // Now temp contains items with largest at top.
  // Transfer all items back to stack to finish.
  while(!temp.empty()) {
    stack.push(temp.top());
    temp.pop();
  }
}


// Possible helping method
template <typename T>
void transfer(std::stack<T>& source, std::stack<T>& destination) {
  destination.push(source.top());
  source.pop();
}

// For testing
template <typename T>
std::string toString(std::stack<T> s) {
  std::stringstream ss;
  std::stack<T> temp;

  while(!s.empty()) {
    temp.push(s.top());
    s.pop();
  }
  while(!temp.empty()) {
    ss << temp.top() << " ";
    s.push(temp.top());
    temp.pop();
  }

  ss << "<-top" << '\n';
  return ss.str();
}

// recursive version of print
template <typename T>
std::string toStringRecursive(std::stack<T> s) {
  std::stringstream ss;
  ss << toStringRecursive(s, s.size()) << "<-top\n";
  return ss.str();
}

template <typename T>
std::string toStringRecursive(std::stack<T>& s, int size) {
  if(size == 0) {
    return ""; 
  }
  if(size == 1) {
    std::stringstream ss;
    ss << s.top();
    return ss.str();
  }
  
  T top_item = s.top();
  s.pop();
  std::stringstream ss;
  ss << toStringRecursive(s, size-1) << " " << top_item;
  s.push(top_item);
  return ss.str();
}
