/*
Intersection:
Given two (singly) linked lists, determine if the two list intersect. 
Return the intersecting node. Note that the intersection is defined 
based on reference, not value. That is, if the kth node of the first 
linked list is the exact same node (by reference) as the jth node of the 
second linked list, then they are intersecting.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "SinglyLinkedList.cpp"

/* 
Method 1: Wrapped Traversal

Time: O(N1 + N2)
Space: O(1)

Traverse both lists at the same time, checking whether the pointers are equal.
If the same length, we will find the intersecting node before reaching the end, 
or if they do not intersect, then they will reach the ends at the same time.

   1 -> 2  ➘                    1  -> 2  -> 3  -> 4  -> 5
            3 -> 4 -> 5    OR   
  10 -> 20 ➚                    10 -> 20 -> 30 -> 40 -> 50

If the have different lengths, they will reach the ends at different times. 
If at an end, wrap around to the start of the OTHER list.
If the lists intersect, they will meet at the same node after wrapping.
If the lists do not intersect, they will reach the ends at the same time.

         1 ➘                    1  -> 2  -> 3  -> 4
            2 -> 3 -> 4    OR   
  10 -> 20 ➚                    10 -> 20 -> 30 -> 40 -> 50

Wrapping to the beginning of the other list guarantees reaching the 
intersecting node at the same time because:

  traversed by current1
  (# in list 1 only) + (# in common) + (# in list 2 only)
  =
  traversed by current2
  (# in list 2 only) + (# in common) + (# in list 1 only)
*/
SinglyLinkedList::Node* intersection_wrap
  (SinglyLinkedList::Node* head1, SinglyLinkedList::Node* head2) {

  SinglyLinkedList::Node* current1 = head1;
  SinglyLinkedList::Node* current2 = head2;

  while(!(current1->next == nullptr && current2->next == nullptr)) {
    // If both point to the same node, return it.
    if(current1 == current2) {
      return current1;
    }
    // Advance both pointers. If at end of list, wrap to the head of the other.
    current1 = current1->next != nullptr ? current1->next : head2;
    current2 = current2->next != nullptr ? current2->next : head1;
  }
  return nullptr;
}

/* Method 3: use std::set

Time: O(N1*insert_in_S1 + N2*find_in_S1)

Traverse list 1 from head to tail and add a pointer to each node to the set.
Then traverse list 2 from head to tail and check whether each node is in set.
Return the first node in list 2 has in common with list 1 
(the intersection point), or finish iterating by reach the end of the list.
*/
SinglyLinkedList::Node* intersection_with_set
  (SinglyLinkedList::Node* head1, SinglyLinkedList::Node* head2) {
    std::set<SinglyLinkedList::Node*> s;
    // Add all Node* in list 1 to set s
    SinglyLinkedList::Node* current = head1;
    while(current != nullptr) {
      s.insert(current);
      current = current->next;
    }
    // Iterate through list 2 from head to tail, 
    // checking whether each node is in the set of nodes from list 1
    current = head2;
    while(current != nullptr) {
      if(s.find(current) != s.end()) {
        return current;
      }
      current = current->next;
    }
    // If we never found any node from list 2 in the set of nodes from list 1
    // return nullptr to mean the lists don't intersect.
    return nullptr;
}

int main() {
  // Test hardcoded lists
  SinglyLinkedList l1; // 1 -> 2 -> 3 -> 4 -> 5
  l1.push_back(1);
  l1.push_back(2);
  l1.push_back(3);
  l1.push_back(4);
  l1.push_back(5);

  SinglyLinkedList l2; // 10 -> 20 -> 4 -> 5 (same 4 and 5 as list l1)
  l2.push_back(10);
  l2.push_back(20);
  // Connect
  l2.nodeAt(1)->next = l1.nodeAt(3);

  // l1:   1 -> 2 -> 3 ➘
  //                    4 -> 5
  // l2:      10 -> 20 ➚   

  std::cout << l1 << '\n';
  std::cout << l2 << '\n';
  printMemoryToEnd(l1.headNode());
  printMemoryToEnd(l2.headNode());
  
  // Lists intersect at node with data: 4
  if(intersection_with_set(l1.headNode(), l2.headNode())) {
    std::cout << "intersection: " << intersection_with_set(l1.headNode(), l2.headNode()) << '\n';
    std::cout << "data: " << intersection_with_set(l1.headNode(), l2.headNode())->data << '\n';
  }
  else {
    std::cout << "No intersection" << '\n';
  }
}
