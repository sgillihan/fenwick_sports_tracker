#ifndef CSVPROCESSOR_H__
#define CSVPROCESSOR_H__

#include <string>
#include <vector>
#include <map>
#include "AthleteTracker.h"

using namespace std;

// CSV Proc exists to process the csv file:
// The CSV file is read in and loaded into AthleteTracker instances
// The dates are parsed from DD/MM/YYYY format into tm structs
// Activities are grouped by athlete, appended in bulk, and Fenwick Trees are rebuilt once per athlete.
namespace CSVProc {
    void importCSV(const string& filename, map<string, AthleteTracker*>& athletes, int treeCapacity = 1000);
    tm parseDate(const string& dateStr);
}

#endif