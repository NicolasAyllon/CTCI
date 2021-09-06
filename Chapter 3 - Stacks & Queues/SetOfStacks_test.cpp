#include <iostream>
#include "SetOfStacks.cpp"

int main() {
  SetOfStacks<int> setOfStacks;
  std::cout << setOfStacks.toStringInternal();

  std::cout << "== Push ==";
  for(int i = 1; i <=64; ++i) {
    std::cout << "Pushing " << i << '\n';
    setOfStacks.push(i);
    std::cout << setOfStacks.toStringInternal();
    std::cout << "Now top is: " << setOfStacks.top() << '\n';
    std::cout << '\n';
  }

  std::cout << "== Pop ==";
  std::cout << '\n';

  while(!setOfStacks.empty()) {
    std::cout << "Popping " << setOfStacks.top() << '\n';
    setOfStacks.pop();
    std::cout << setOfStacks.toStringInternal();
    std::cout << '\n';
  }
  return 0;
}