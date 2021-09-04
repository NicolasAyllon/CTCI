#include <iostream>
#include "Stack_Array.cpp"

int main() {
  Stack_Array<int> s;
  std::cout << s.toString() << '\n';
  // std::cout << "top element is: " << s.top() <<'\n'; 
  // uncomment above line to verify it throws an error for an empty stack
  std::cout << "\n";

  // Push
  for(int i = 1; i <= 32; ++i) {
    std::cout << "pushing " << i << " to stack" << '\n';
    s.push(i);
    std::cout << s.toStringInternal() << '\n';
    std::cout << "top element is: " << s.top() <<'\n';
    std::cout << "size: " << s.size() << '\n';
    std::cout << "capacity: " << s.capacity() << '\n';
    std::cout << '\n';
  }

  // Pop
  while(!s.empty()) {
    std::cout << "popping " << s.top() << " from stack" << '\n';
    s.pop();
    std::cout << s.toStringInternal() << '\n';
    std::cout << "size: " << s.size() << '\n';
    std::cout << "capacity: " << s.capacity() << '\n';
    std::cout << '\n';
  }
}