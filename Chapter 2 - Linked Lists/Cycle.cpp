/*
Cycle:
Given a circular linked list, implement an algorithm that returns the node 
at the beginning of the loop.

Note: A circular linked list is a (corrupt) list in which a node's next
pointer points to an earlier node, so as to make a loop in the linked list.
*/

#include <iostream>
#include <unordered_set>
#include "SinglyLinkedList.cpp"

/* Method 1: use std::unordered_set

Time: O(N)
Space: O(N)

Use an std::unordered_set to track visited nodes and check whether a node 
has been visited. Lookup and insertion are O(1).
*/
SinglyLinkedList::Node* getCycleStart(SinglyLinkedList::Node* head) {
  // Initialize current and create unordered set for visited nodes
  SinglyLinkedList::Node* current = head;
  std::unordered_set<SinglyLinkedList::Node*> visited;
  // Traverse the list from the head to tail.
  while(current != nullptr) {
    // Check whether this node has been visited
    if(visited.find(current) != visited.end()) {
      // The current node has already been visited
      // so this node is the start of the cycle. Return it.
      return current;
    }
    // Otherwise, we haven't visited this node before, so put it in the set,
    // and advance current.
    visited.insert(current);
    current = current->next;
  }
  // If we reach the end of the list without revisiting any nodes, 
  // the list has no cycles, so return nullptr.
  return nullptr;
}


/* Method 2: Floyd's algorithm

Time: O(N)
Space: O(1)

Launch slow and fast pointers from head.
If the fast pointer reaches the end of the list, there are no cycles. 

If the fast and slow pointers meet, there is a cycle, but this meeting point is
not necessarily the start of the cycle. 

It's possible to show that if a second slow pointer is launched from the head 
when the fast and slow pointers meet, it will meet the first slow pointer at
the start of the cycle.

*/
SinglyLinkedList::Node* getCycleStart_Floyd(SinglyLinkedList::Node* head) {
  // A linear list with 0 or 1 nodes has no cycles.
  if(head == nullptr || head->next == nullptr) return nullptr;
  // Otherwise, the list has 2+ nodes (or is a 1-cycle).
  SinglyLinkedList::Node* slow = head;
  SinglyLinkedList::Node* fast = head;
  // First advance (so that slow != fast)
  slow = slow->next;
  fast = fast->next->next;
  // Advance both pointers until fast meets slow 
  while(fast != slow) {
    slow = slow->next;
    fast = fast->next->next;
    // If fast reaches the end, immediately return nullptr for no cycles.
    if(fast == nullptr || fast->next == nullptr) return nullptr;
  }
  // At the meeting point, launch a second slow pointer from the head.
  // Advance both slow pointers until they meet at the start of the cycle.
  SinglyLinkedList::Node* slow2 = head;
  while(slow != slow2) {
    slow = slow->next;
    slow2 = slow2->next;
  }
  // slow and slow2 meet at the start of the cycle, so return that node.
  return slow;
}


/* * * * * * * * * * * * Convenience Functions * * * * * * * * * * * * * * */
// built on getCycleStart() above.


bool containsCycle(SinglyLinkedList::Node* head) {
  return getCycleStart(head) != nullptr;
}

// Find the length of the cycle. If the list has no cycles, return 0.
int getCycleLength(SinglyLinkedList::Node* head) {
  SinglyLinkedList::Node* start = getCycleStart(head);
  // If there are no cycles, immediately return 0
  if(start == nullptr) return 0;
  // Otherwise create a current pointer to traverse the cycle and 
  // count how many nodes it visits to get back to the start.
  SinglyLinkedList::Node* current = start->next;
  int length = 1;
  while(current != start) {
    current = current->next;
    length++;
  }
  return length;
}


int main() {
  SinglyLinkedList list;
  list.push_back(0);
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);
  list.push_back(6);
  list.push_back(7);
  list.push_back(8);
  list.push_back(9);
  // Create cycle
  list.nodeAt(9)->next = list.nodeAt(3);

  if(containsCycle(list.headNode())) {
    std::cout << "cycle detected starting at: " 
              << getCycleStart_Floyd(list.headNode()) << '\n';
    std::cout << "data: "
              << getCycleStart_Floyd(list.headNode())->data << '\n';
    std::cout << "length of cycle: " 
              << getCycleLength(list.headNode()) << '\n';
  }
  else {
    std::cout << "No cycles detected" << '\n';
  }
}