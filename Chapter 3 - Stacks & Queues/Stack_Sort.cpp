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
  // std::cout << "Initial State: \n";
  // std::cout << "stack: " << toString(stack);
  // std::cout << "temp : " << toString(temp);
  // std::cout << '\n';
  while(!stack.empty()) {
    // The temporary stack is empty or the next item in the stack is
    // correctly ordered (greater than the previous one, now on top of temp).
    // So, transfer item to temp.
    if(temp.empty() || stack.top() >= temp.top()) {
      // if(temp.empty()) {
      //   std::cout << "Temp empty. Transfering element from stack...\n";
      // }
      // else {
      //   std::cout << "temp top < stack top: " 
      //             << temp.top() << " < " << stack.top() 
      //             << ". Correct so far." << '\n';
      // }
      temp.push(stack.top());
      stack.pop();
      // std::cout << "Transfer: \n";
      // std::cout << "stack: " << toString(stack);
      // std::cout << "temp : " << toString(temp);
      // std::cout << '\n';
      continue;
    }
    // The next item in the stack (top) is less than previous (at top of temp)
    // which means this element is out of order.
    // Save to cache and put back in order.
    cache = stack.top();
    stack.pop();
    // std::cout << "\titem " << cache << " is out of order!";
    // std::cout << "\tcached: " << cache << '\n';
    // std::cout << '\n';
    // std::cout << "\tCache: [" << cache << "]" << '\n';
    // std::cout << "\tstack: " << toString(stack);
    // std::cout << "\ttemp : " << toString(temp);
    // std::cout << '\n';
    // std::cout << "\tfinding right place for " << cache << "...\n";
    // std::cout << '\n';
    while(!temp.empty() && cache < temp.top()) {
      stack.push(temp.top());
      temp.pop();
      // std::cout << "\ttransfer: \n";
      // std::cout << "\tCache: [" << cache << "]" << '\n';
      // std::cout << "\tstack: " << toString(stack);
      // std::cout << "\ttemp : " << toString(temp);
      // std::cout << '\n';
    }
    stack.push(cache);
    // std::cout << "\tfound right place, pushing cache onto stack...\n";
    // std::cout << "\tstack: " << toString(stack);
    // std::cout << "\ttemp : " << toString(temp);
    // std::cout << '\n';

  }
  // All items transfered from stack to temp and no out-of-order items found.
  // Now temp contains items with largest at top.
  // Transfer all items back to stack to finish.
  // std::cout << "---------------------------------------------------------\n";
  // std::cout << "Sorting complete in reverse on temp. Transfer to stack...\n";
  // std::cout << "---------------------------------------------------------\n";
  while(!temp.empty()) {
    stack.push(temp.top());
    temp.pop();
    // std::cout << "Transfer: \n";
    // std::cout << "stack: " << toString(stack);
    // std::cout << "temp : " << toString(temp);
    // std::cout << '\n';
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

//[?] recursive version of print
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
