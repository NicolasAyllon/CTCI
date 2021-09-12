#include <iostream>
#include <stack>
#include "Stack_Sort.cpp"

int main() {
  // Test hardcoded stack with ints
  std::stack<int> test_stack;
  test_stack.push(3);
  test_stack.push(4);
  test_stack.push(2);
  test_stack.push(5);
  test_stack.push(1);
  test_stack.push(9);
  test_stack.push(6);
  test_stack.push(8);
  test_stack.push(7);

  std::cout << "before:\n";
  std::cout << toString(test_stack);
  SortStack(test_stack);
  std::cout << "after:\n";
  std::cout << toString(test_stack);

  // Test hardcoded stack with chars
  std::stack<char> test_stack_2;
  test_stack_2.push('N');
  test_stack_2.push('I');
  test_stack_2.push('C');
  test_stack_2.push('O');
  test_stack_2.push('L');
  test_stack_2.push('A');
  test_stack_2.push('S');

  std::cout << "before:\n";
  std::cout << toString(test_stack_2);
  SortStack(test_stack_2);
  std::cout << "after:\n";
  std::cout << toString(test_stack_2);

  return 0;
}