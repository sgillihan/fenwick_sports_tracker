#ifndef FENWICKTREE_H__
#define FENWICKTREE_H__

#include <vector>
#include <string>

using namespace std;

// The Fenwick Tree class manages the structure of the tree and enables prefix sum and 
// range sum query operations for stored values (currently distance and time).

class FenwickTree {
  private:

  // The tree itself is stored as a vector of partial sums (double format)
  vector <double> tree;

  // The size of the tree is set to 1000 by default
  int size;

  // The name of the tree is a combination of the athlete name and "time" or "distance"
  string name;

  public:
  FenwickTree(int n, const string& treeName="Unnamed"); //Constructor- default size is 1000
  //~FenwickTree(); //Destructor- not currently needed

  // updates the tree at the provided index by adding the delta (difference) between existing value and new value
  void update(int index, double delta);

  // Query goes to the provided index to find the cumulative sum at that location
  // This is actually querying from index 0 to the given index (inclusive)
  double query(int index) const;

  // Range Query goes to the start and end indices and finds the cumulative sum of the range by subtracting those values
  double rangeQuery(int start, int end) const;

  // Provides size (capacity) of tree
  int getSize() const;

  // Provides name of tree- used for other function calls
  const string& getName() const;

  // The print Fenwick Trees function is the primary method of illustrating the inner workings of a Fenwick Tree
  // Raw values, tree nodes, and cumulative query paths are all printed.
  // Print Fenwick Tree allows the user to see how the cumulative sums are stored over large amounts of data,
  // and allows the user to see how the query operation jumps through different indices to access cumulative sums in
  // O(log n) time
  void printFenwickDetails(const vector<double>& rawData) const;
  
};

#endif


 