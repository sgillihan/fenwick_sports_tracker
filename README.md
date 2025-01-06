# Graphs

## Overview 

A Graph is a versatile, powerful data structure that is conceptually simple -
they're drawn as boxes and arrows - but can in practice become quite complex
depending on the use case. Graphs can be used to model many things, such as
traffic in a city, flowcharts, affinity between people in a social network, the
state of an embedded system, or electric brain cells in an artificial neural
network.

They can be implemented in various ways, such as with a sparse matrix, or
adjacency lists, or with nodes and edges. For this assignment, we'll take the
"node and edge" approach similar to what we did for BST and B-Trees.

In this assignment, you'll implement a graph data structure and breadth-first
and depth-first algorithms to operate on that graph. Check out this week's video
lectures cover various ways to implement graphs, design decisions regarding
storing metadata, and common graph algorithms.  

## Goals

* Implement an graph composed of nodes and edges
* The graph can be configured to be directed (meaning the edges have arrowheads)
  or undirected
* Apply metadata to nodes and edges to manage state for algorithms
* Implement key graph algorithms including BFS and DFS

There is a lot of code that has been written for you. You'll need to implement
the functions with `// TODO` in them. There are about ten functions in total for
you to implement.

## This is Object-Oriented

This assignment brings back a class-based approach because it can be used to
organize your code nicely. You'll have header files for the Node and Edge
classes, and they are tied together with the Graph class. 

The Node and Edge classes mostly just store node- and edge-related data. The
Graph class holds vectors of the nodes and edges, and a boolean that determines
if the graph's edges are directed or not.

The Graph class also has DFS and BFS methods for you to implement.

In your implementation, be sure you only edit the Graph/Node/Edge `.cpp` files.


## Useful Tips 	   

This assignment is very detail-oriented, so refer to the lecture videos and
slides as needed.

### Go in order

It is recommended that you implement the functions in the same order that
they appear in the test file.

### Pseudocode

This is the pseudocode to get you going. You'll need to augment it
(e.g. by setting ancestors, incrementing the clock, classifying edges,
and so on).

```
bfs(start):
  clear graph
  mark start gray
  Q = empty queue
  add start to Q
  while Q has stuff in it:
    v = popped element from Q
    mark v black
    visit v
    for each unmarked neighbor w
        mark w gray
        add w to Q
```

```
# clear graph before initial call
dfs(node): 
  mark node gray
  visit node
  E = edges related to node
  for all edges e in E:
    a = end of e that isn't node
    if a is white:
      dfs(a)
  mark node black
```

### Two versions of bfs

There are two signatures for bfs. If you implement the two-arg version fully,
then you can have the one-arg version simply call the two-arg version with a
target that doesn't exist in the graph.

Remember: laziness is one of the three virtues of a great programmer.

### Use a queue, maybe

The header file includes vectors to store nodes and edges during a search
(`search_edges` and `search_nodes`). You can use these if you like, or ignore
them and use something else instead.

One possible alternative implementation: an iterative BFS using a queue (so,
`#include <queue>` atop implementation file), and a recursive DFS using the
`getAdjacentEdges` set.

### The auto keyword

The `auto` keyword can make life easier when iterating through a collection. It
leverages the compiler to 'figure out' what type would be assigned for you (this
only works for assignment, you cannot use `auto` for example in function
parameters). Also note that it is NOT like Python's dynamic types, the type must
still be known at compile time.

You can use `auto` to cleanly iterate over C++ collections:

```cpp
for (auto n : nodes) {
  // n right here will be a single node, one at a time.
}
```

A more correct way to handle iteration (which forces const and that the value is
iterated by reference resulting in zero-copy):

```cpp
for (const auto& n : nodes) {
  // n right here will be a single node, one at a time.
}
```

### Use `make_dot`

Check out the `tick` and `make_dot` functions provided for you in the
implementation file. If you call `tick` after each interesting event (start,
end, and every time you increment the clock) you can use this to watch the
progress of your `dfs` or `bfs`.

The `make_dot` function will output text that can be used in an online
"Graphviz" viewer like the one at https://dreampuf.github.io/GraphvizOnline. You
might have used this for a previous assignment.

### Make helper functions

You'll likely want to create and use helper functions. The details are up to
you. For example, there is an `otherEnd` function that returns the opposite end
of an edge.

Helpers aren't strictly necessary but they will make your life easier
and reduce the volume of code where bugs can lurk.

### Node discovery colors

Node color tells us if we have discovered a node, if we're in the middle of
finishing a node, or if we've finished a node. They are:

`WHITE`: Node has not yet been reached by the search.

`GRAY`: Node has been reached by the search but is not yet complete.

`BLACK`: Node has been completely explored.

### Edge Types

Edge type tells us information about how the path was discovered during a
depth-first search, and it also might give us valuable information about the
shape of the graph. There are four kinds of edges, though it is not necessary to
use all of them all of the time. They are:

`TREE`: A tree edge from A to B indicates that B was discovered via A.

`BACK`: A back edge from C to A indicates that A was discovered before C, and C
was discovered while A was still being explored.

`FORWARD`: A forward edge from A to C indicates that C was completely examined
when we found it, and A is an ancestor of C in the DFS spanning tree.

`CROSS`: A cross edge from A to C indicates the C was completely examined when we
found it, and A is NOT an ancestor of C in the DFS spanning tree.

These edge types are summarized graphically at
http://en.wikipedia.org/wiki/Depth-first_search and does a much better job than
words can do.

To determine edge types, you need to use both the discovery information (the
color of the ending node) and the predecessor information (to distinguish
between Cross and Forward edges).

Tree edges are when the end node is white.

Back edges are when the end node is gray.

Forward and cross edges are when the end node is black. If the start node is an
ancestor of the end node, it is a forward edge. Otherwise it is a cross edge.