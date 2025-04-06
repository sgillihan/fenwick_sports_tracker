#include "Graph.h"

#include <iostream>
#include <sstream>

using namespace std;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  // DONE FOR YOU
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
  // "DONE" FOR YOU
  // no implementation needed
}

vector<Node*> Graph::getNodes() {
  // DONE FOR YOU
  return nodes;
}

vector<Edge*> Graph::getEdges() {
  // DONE FOR YOU
  return edges;
}

int Graph::getClock() {
  // DONE FOR YOU
  return clock;
}

void Graph::addNode(Node* n) {
  // DONE FOR YOU
  nodes.push_back(n);
}

void Graph::addEdge(Edge* e) {
  // DONE FOR YOU
  edges.push_back(e);
}

void Graph::removeNode(Node* n) {
  // DONE FOR YOU
  for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}

void Graph::removeEdge(Edge* e) {
  // DONE FOR YOU
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  // DONE FOR YOU
  directed = val;
}

bool Graph::isDirected() {
  // DONE FOR YOU
  return directed;
}

set<Edge*> Graph::getAdjacentEdges(Node* n) {
  // DONE FOR YOU
  set<Edge*> ret;
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    Edge* edge = *it;
    if (edge->getStart() == n) {
      ret.insert(edge);
    }
    if (!directed && (edge->getEnd() == n)) {
      ret.insert(edge);
    }
  }
  return ret;
}

void Graph::clear() {
  // clear nodes
  for (const auto& n : getNodes()) {
    n->clear();
  }
  //clear edges
  for (const auto& e : getEdges()) {
    e->setType(UNDISCOVERED_EDGE);
  }
  //clear lists
  search_edges.clear();
  search_nodes.clear();
  clock=0;
}

void Graph::tick(string message) {
  // DONE FOR YOU
  //
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning. Change this however you want.
  //
  // recommended use: call it just after incrementing the clock.
  if (false) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}

void Graph::dfs(Node* start) {
  // clear graph before initial call
  if (clock==0 && search_nodes.empty()){
    clear();
  }
  
  // visit the node
  start->setColor(GRAY,clock);
  clock++;
  search_nodes.push_back(start);
  
  // get all adjacent edges
  set<Edge*> curr_edges = getAdjacentEdges(start);

  // for each edge in adjacent edges
  for (const auto& e : curr_edges) {
    Node* neighbor=nullptr;
    if (!isDirected() || e->getStart()==start){
      //Node* neighbor=nullptr;
      if (e->getStart()==start){
        neighbor = e->getEnd();
      }
      else{
        neighbor = e->getStart();
      }
    }
    else {
      continue;
    }
  
    int color,disc,comp,rank;
    neighbor->getDiscoveryInformation(color,disc,comp,rank);

    // the neighbor is undiscovered. Neighbor was discovered via start. This is a tree edge
    if (color==WHITE){
      e->setType(TREE_EDGE);
      neighbor->setPredecessor(start);
      dfs(neighbor);
    }

    // the neighbor is discovered but not completely processed. This is a back edge
    else if (color==GRAY) {
      e->setType(BACK_EDGE);
    }

    // the neighbor is discovered and completely processed. If start is ancestor of neighbor, forward edge. Else, cross edge
    else if (color==BLACK){
      if (neighbor->isAncestor(start)){
        e->setType(FORWARD_EDGE);
      }
      else{
        e->setType(CROSS_EDGE);
      }
    }
    search_edges.push_back(e);
  }
start->setColor(BLACK,clock);
clock++;
}

void Graph::bfs(Node* start) {

}

void Graph::bfs(Node* start, Node* finish) {
  // TODO
}

// overloading operator << lets you put a Graph object into an output
// stream.
ostream& operator<<(ostream& out, Graph graph) {
  // DONE FOR YOU
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<Node*>::iterator it = graph.nodes.begin();
       it != graph.nodes.end(); it++) {
    Node* n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<Edge*>::iterator it = graph.edges.begin();
       it != graph.edges.end(); it++) {
    Edge* e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness.
string what(int& v) {
  // DONE FOR YOU
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}

// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  // DONE FOR YOU
  stringstream ss;
  vector<Node*> nodes = g->getNodes();
  vector<Edge*> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " homework {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it = nodes.begin(); it != nodes.end(); ++it) {
    Node* n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\""
       << textColor << "\" fillcolor=\"" << what(c) << "\""
       << " ]" << endl;
  }

  string edgeColor = "black";
  for (auto it = edges.begin(); it != edges.end(); ++it) {
    Edge* e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData()
       << " [color=\"" << edgeColor << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}