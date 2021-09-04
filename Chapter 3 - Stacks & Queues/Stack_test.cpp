#include <iostream>
#include <cassert>
#include "Stack.cpp"

int main() {
  Stack<int> s; 
  // Possible to make template arg <int> implied, so that the following works?
  // Stack s;

  // Pushing
  assert(s.size() == 0);        // top ->
  assert(s.empty() == true);
  // top -> 5
  s.push(5);                    // top -> 5
  assert(s.size() == 1);
  assert(s.empty() == false);
  assert(s.top() == 5);
  assert(s.min() == 5); // Stack_Min

  s.push(2);                    // top -> 2 -> 5
  assert(s.min() == 2);

  s.push(3);                    // top -> 3 -> 2 -> 5
  assert(s.top() == 3);
  assert(s.min() == 2); // Stack_Min

  s.push(1);                    // top -> 1 -> 3 -> 2 -> 5
  assert(s.min() == 1); // Stack_Min



  // Popping
  s.pop();                      // top -> 3 -> 2 -> 5
  assert(s.top() == 3);
  assert(s.min() == 2);  // Stack_Min

  s.pop();                      // top -> 2 -> 5
  assert(s.min() == 2);  // Stack_Min

  s.pop();                      // top -> 5
  assert(s.min() == 5);  // Stack_Min

  s.pop();                      // top ->
  assert(s.empty() == true);
  
  std::cout << "testing toString(): " << s.toString() << '\n';
  std::cout << "testing << overload: " << s << '\n';
  return 0;
}