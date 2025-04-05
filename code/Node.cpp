#include "Node.h"

Node::Node(string s) {
  // DONE FOR YOU
  data = s;
}

Node::~Node() {
  // "DONE" FOR YOU
  //
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}

string Node::getData() {
  // DONE FOR YOU
  return data;
}

void Node::setRank(int r) {
  // DONE FOR YOU
  rank = r;
}

void Node::clear() {
  color = WHITE;
  discovery_time=-1;
  completion_time=-1;
  rank=-1;
  predecessor=nullptr;
}

void Node::setColor(int search_color, int time) {
  if (search_color==GRAY){
    color=GRAY;
    discovery_time=time;
  }
  else if (search_color==BLACK){
    color=BLACK;
    completion_time=time;
  }
  else if (search_color==WHITE){
    clear();
  }
}

void Node::getDiscoveryInformation(int& thecolor, int& disco_time,
                                   int& finish_time, int& bfs_rank) {
                                    thecolor = color;
                                    disco_time=discovery_time;
                                    finish_time=completion_time;
                                    bfs_rank=rank;
}

bool Node::isAncestor(Node* other) {
  Node* curr_node=this;
  while (curr_node != nullptr){
    if (curr_node==other){
      return true;
    }
    curr_node = curr_node->predecessor;
  }
  return false;
}

void Node::setPredecessor(Node* other) {
  predecessor=other;
}

// overloading operator << lets you put a Node object into an output
// stream.
ostream& operator<<(std::ostream& out, Node node) {
  // DONE FOR YOU
  out << node.data;
  return out;
}
