#include "CSVProc.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

tm CSVProc::parseDate(const string& dateStr) {
    tm date = {};
    sscanf(dateStr.c_str(), "%d/%d/%d", &date.tm_mon, &date.tm_mday, &date.tm_year);

    date.tm_mon -= 1; // month 0-11
    date.tm_year -= 1900; // year since 1900
    return date;
}

void CSVProc::importCSV(const string& filename, map<string,AthleteTracker*>& athletes, int treeCapacity){
    ifstream file(filename);
    if (!file.is_open()){
        cerr<<"Failed to open file: " << filename<< endl;
        return;
    }

    string line;
    getline(file, line); //skip header

    // Group activities by name so they can be appended in bulk, and Fenwick tree is built once
    map<string,vector<Activity>> tempActivities;

    while (getline(file, line)) {
        istringstream ss(line);
        string name, dateStr, distStr, timeStr;

        if (!getline(ss,name,',')) continue;
        if (!getline(ss,dateStr,',')) continue;
        if (!getline(ss,distStr,',')) continue;
        if (!getline(ss,timeStr,',')) continue;

        // stod is a standard library feature that converts a string to a double
        tm date = parseDate(dateStr);
        double distance = stod(distStr);
        double time = stod(timeStr);

        Activity a;
        a.name = name;
        a.date = date;
        a.distance = distance;
        a.time = time;

        tempActivities[name].push_back(a);

    }
    file.close();

    for (auto& [name, acts] : tempActivities) {
        if (athletes.find(name)== athletes.end()) {
            athletes[name]= new AthleteTracker(name, treeCapacity);
        }

        for (auto& a : acts) {
            a.id = athletes[name]->getNextActivityId();
            athletes[name]->appendActivityWithoutRebuild(a);
        }

        athletes[name]->rebuildTrees();
    }

}