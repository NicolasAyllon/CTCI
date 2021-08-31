#include <iostream>
#include <cassert>
#include "Stack.cpp"

int main() {
  Stack<int> s; 
  // Possible to make template arg <int> implied, so that the following works?
  // Stack s;
  assert(s.size() == 0);
  assert(s.empty() == true);

  s.push(5);
  std::cout << s << '\n';
  assert(s.size() == 1);
  assert(s.empty() == false);
  assert(s.top() == 5);

  s.push(3);
  std::cout << s << '\n';
  assert(s.size() == 2);
  assert(s.top() == 3);


  s.pop();
  std::cout << s << '\n';
  assert(s.size() == 1);
  assert(s.top() == 5);

  s.pop();
  std::cout << s << '\n';
  assert(s.empty() == true);
  //std::cout << s;
  std::cout << "testing toString(): " << s.toString() << '\n';
  std::cout << "testing << overload: " << s << '\n';
  return 0;
}