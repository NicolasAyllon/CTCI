#include <iostream>
#include "Graph.cpp"

int main() {
  Graph g;
  g.addVertex(1);
  g.addVertex(2);
  g.addVertex(3);
  g.addVertex(4);

  std::cout << g.toString() << '\n';
  return 0;
}