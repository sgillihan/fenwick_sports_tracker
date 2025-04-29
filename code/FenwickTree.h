#ifndef FENWICKTREE_H__
#define FENWICKTREE_H__

#include <vector>
#include <string>

using namespace std;

class FenwickTree {
  private:
  vector <double> tree;
  int size;
  string name;

  public:
  FenwickTree(int n, const string& treeName="Unnamed"); //Constructor
  ~FenwickTree(); //Destructor

  void update(int index, double delta);
  double query(int index) const;
  double rangeQuery(int start, int end) const;
  int getSize() const;
  const string& getName() const;
  void printFenwickDetails(const vector<double>& rawData) const;
  
};

#endif


 