#ifndef CSVPROCESSOR_H__
#define CSVPROCESSOR_H__

#include <string>
#include <vector>
#include <map>
#include "AthleteTracker.h"

using namespace std;

namespace CSVProc {
    void importCSV(const string& filename, map<string, AthleteTracker*>& athletes, int treeCapacity = 1000);
    tm parseDate(const string& dateStr);
}

#endif