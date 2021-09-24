/*
Graph is an implementation of an undirected, unweighted graph 
(without self-directed loops) represented as an adjacency list/set.
*/

#include <iostream>
#include <sstream>
#include <map>
#include <set>

class Graph {
 private:
  std::map<int, std::set<int>> vertices_;

 public:
  Graph();
  ~Graph();
  void addVertex(int vertex);
  void removeVertex(int vertex);
  void addEdge(int vertex_a, int vertex_b);
  void removeEdge(int vertex_a, int vertex_b);
  // Utilities
  bool contains(int vertex) const;
  int degreeOf(int vertex) const;
  bool isDirectlyConnected (int vertex_a, int vertex_b) const;
  bool isEulerian() const;
  std::string toString() const;
};



Graph::Graph() {}

Graph::~Graph() {}

// If the vertex (key) is not already in the map, insert it
// and map it to an empty default-constructed std::set<int>.
void Graph::addVertex(int vertex) {
  if(vertices_.find(vertex) == vertices_.end()) {
    vertices_[vertex] = std::set<int>();
  }
}


void Graph::removeVertex(int vertex) {
  // Do nothing if there was no such vertex
  if(!contains(vertex)) return;
  // Erase this vertex from all of its neighbor's adjacency sets
  for(int neighbor : vertices_[vertex]) {
    vertices_[neighbor].erase(vertex);
  }
  // Finally, erase the vertex from the map
  vertices_.erase(vertex);
}

// Adds an edge and any required vertices if not already in the graph.
void Graph::addEdge(int vertex_a, int vertex_b) {
  // Ignore attempts to form self-directed loops
  if(vertex_a == vertex_b) return;

  // std::map's operator[] will automatically default-construct the 
  // value object (an empty std::set<int>) if key (int) is not found.
  //     map[key]
  //          ↓
  vertices_[vertex_a].insert(vertex_b);
  vertices_[vertex_b].insert(vertex_a);
  //                    ↑
  // Afterwards, std::set ensures no duplicate nodes are inserted
}


void Graph::removeEdge(int vertex_a, int vertex_b) {
  // Ignore attempts to remove loops
  if(vertex_a == vertex_b) return;
  // Erase b from a's neighbor set and erase a from b's neighbor set
  if(contains(vertex_a) && contains(vertex_b)) {
    vertices_[vertex_a].erase(vertex_b);
    vertices_[vertex_b].erase(vertex_a);
  }
}


bool Graph::contains(int vertex) const {
  return vertices_.find(vertex) != vertices_.end();
}


int Graph::degreeOf(int vertex) const {
  if(!contains(vertex)) {
    return -1;
  }
  return vertices_.at(vertex).size();
  // Note:
  //   return vertices_[vertex].size();
  // doesn't work because operator[] is not const
  // because it default-constructs missing keys, 
  // which changes the std::map (vertices_).
  // 
  // Instead use at(--key--) which has a const version.
}


bool Graph::isDirectlyConnected(int vertex_a, int vertex_b) const {
  // If either vertex is not in the graph, return false
  if(!contains(vertex_a) || !contains(vertex_b)) {
    return false;
  }
  // Otherwise return whether b is found in a's neighbor set
  auto it = vertices_.at(vertex_a).find(vertex_b);
  return it != vertices_.at(vertex_a).end();
}

// A graph is Eulerian if the number of vertices 
// with an odd number of edges is equal to 0 or 2.
bool Graph::isEulerian() const {
  int odd_degree_vertices = 0;
  for(auto it = vertices_.begin(); it != vertices_.end(); ++it) {
    // it->second is the set of neighbors of each vertex
    if(it->second.size() % 2 == 1) {
      odd_degree_vertices++;
    }
  }
  return (odd_degree_vertices == 0 || odd_degree_vertices == 2);
}


std::string Graph::toString() const {
  std::stringstream ss;
  for(auto it_map = vertices_.begin(); it_map != vertices_.end(); ++it_map) {
    // insert vertex into ss
    ss << it_map->first << " -> ";
    // insert neighbors into ss
    const std::set<int>& neighbors = it_map->second;
    if(!neighbors.empty()) {
     // the first
      auto it_set = neighbors.begin();
      ss << *it_set;
      ++it_set;
      // the rest
      for(; it_set != neighbors.end(); ++it_set) {
        ss << ", " << *it_set;
      }
    }
    ss << '\n';
  }
  return ss.str();
}

