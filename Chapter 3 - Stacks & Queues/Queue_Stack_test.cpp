#include <iostream>
#include "Queue_Stack.cpp"

int main() {
  Queue_Stack<int> queue;

  // Push
  for(int i = 1; i <= 10; ++i) {
    std::cout << "Enqueue " << i << '\n';
    queue.enqueue(i);
    std::cout << queue.toStringInternal();
    std::cout << "Front: " << queue.front() << '\n';
    std::cout << "Back: " << queue.back() << '\n';
    std::cout << '\n';
    std::cin.get();
  }

  // Pop
  while(!queue.empty()) {
    std::cout << "Dequeue " << queue.front() << '\n';
    queue.dequeue();
    std::cout << queue.toStringInternal();
    if(!queue.empty()) {
      std::cout << "Front: " << queue.front() << '\n';
      std::cout << "Back: " << queue.back() << '\n';
    }
    std::cout << '\n';
    std::cin.get();
  }

  return 0;
}