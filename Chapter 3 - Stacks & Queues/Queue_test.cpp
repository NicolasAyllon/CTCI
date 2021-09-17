#include <iostream>
#include <cassert>
#include "Queue.cpp"

int main() {
  Queue<int> queue;
  assert(queue.size() == 0);
  assert(queue.empty() == true);
  std::cout << queue << '\n';       // front->  <-back
  
  // Enqueue 3
  queue.enqueue(3);
  assert(queue.size() == 1);
  assert(queue.empty() == false);
  assert(queue.front() == 3);
  std::cout << queue << '\n';       // front-> 3 <-back

  // Enqueue 5
  queue.enqueue(5);
  assert(queue.size() == 2);
  assert(queue.empty() == false);
  assert(queue.front() == 3);
  assert(queue.back() == 5);
  std::cout << queue << '\n';       // front-> 3, 5 <-back

  // Enqueue 7
  queue.enqueue(7);
  assert(queue.back() == 7);
  assert(queue.size() == 3);
  std::cout << queue << '\n';       // front-> 3, 5, 7 <-back

  // Dequeue (3)
  queue.dequeue();
  assert(queue.front() == 5);
  assert(queue.back() == 7);
  assert(queue.size() == 2);
  std::cout << queue << '\n';       // front-> 5, 7 <-back

  // Dequeue (5)
  queue.dequeue();
  assert(queue.front() == 7);
  assert(queue.back() == 7);
  assert(queue.size() == 1);
  assert(queue.empty() == false);
  std::cout << queue << '\n';       // front-> 7 <-back

  // Dequeue (7)
  queue.dequeue();
  // Uncomment the following print statements to check
  // front() and back() throw an error on empty queue
  // ----------------------------------
  // std::cout << queue.front() << '\n';
  // std::cout << queue.back() << '\n'; 
  assert(queue.size() == 0);
  assert(queue.empty() == true);
  std::cout << queue << '\n';       // front->  <-back

  return 0;
}