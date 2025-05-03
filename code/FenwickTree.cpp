#include "FenwickTree.h"
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

FenwickTree::FenwickTree(int n, const string& treeName) : size(n), name(treeName) {
    tree.resize(n + 1, 0.0);
}

//FenwickTree::~FenwickTree(){
// no action needed
//}

const string& FenwickTree::getName() const {
  return name;
}

//updates the index and all affected parent indices using bit operations
void FenwickTree::update(int index, double delta) {
    for (++index; index <= size; index += index & -index) {
        tree[index] += delta;
    }
}

double FenwickTree::query(int index) const {
    double sum = 0.0;
    for (++index; index > 0; index -= index & -index) {
        sum += tree[index];
    }
    return sum;
}

double FenwickTree::rangeQuery(int left, int right) const {
    return query(right) - query(left - 1);
}

int FenwickTree::getSize() const {
    return size;
}

void FenwickTree::printFenwickDetails(const vector<double>& rawData) const {
    cout << "\nDetailed Fenwick Tree View (" << name << ")\n";
    cout << left
         << setw(8) << "Index"
         << setw(12) << "Distance"
         << setw(18) << "Raw tree[i]"
         << setw(22) << "Cumulative query(i)"
         << "Nodes used in query(i)" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < size; ++i) {
        double distance = (i < rawData.size()) ? rawData[i] : 0.0;
        double rawStored = tree[i+1]; 
        double cumulative = query(i);

        cout << left
             << setw(8) << i
             << setw(12) << distance
             << setw(18) << rawStored
             << setw(22) << cumulative;

        // Print which nodes are used during query
        cout << "[ ";
        int idx = i + 1;
        while (idx > 0) {
            cout << "tree[" << idx << "] ";
            idx -= idx & -idx;
        }
        cout << "]" << endl;
    }
    cout << endl;
}



