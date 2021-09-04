#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "Stack.cpp"


// template <typename T>
// T min_bruteforce(Stack<T> stack) {
//   // Throw error on empty stack
//   if(stack.empty()) { throw std::logic_error("Stack is empty"); }

//   T min = stack.top();
//   stack.pop();

//   while(!stack.empty()) {
//     if(stack.top() < min) {
//       min = stack.top();
//     }
//     stack.pop();
//   }
//   return min;
// }


int main() {
  std::ifstream testFile("Stack_Min_test.txt");
  if(testFile.is_open()) {
    std::string line;
    while(std::getline(testFile, line)) {
      Stack<int> stack;
      std::stringstream ss_line(line);

      int item;
      while(ss_line >> item) {
        stack.push(item);
        std::cout << "pushing " << item << ", min = " << stack.min() << '\n';
      }

      std::cout << stack << '\n';
      while(!stack.empty()) {
        int popped = stack.top();
        stack.pop();
        std::cout << "popped " << popped;
        if(!stack.empty()) {
          std::cout << ", min = " << stack.min() << '\n';
        }
        else {
          std::cout << ", empty" << '\n';
        }
      }
    }
  }
  return 0;
}