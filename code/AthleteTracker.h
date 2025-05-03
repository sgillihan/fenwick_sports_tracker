#ifndef ATHLETETRACKER_H__
#define ATHLETETRACKER_H__

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include "FenwickTree.h"
#include "Activity.h"

using namespace std;

class AthleteTracker {
private:
    string athleteName;
    vector<Activity> activities;
    map<int, int> idToIndexMap; // unique activity ID to be used in tree
    map<int, int> indexToIdMap; // reverse ID lookup
    map<string,vector<int>> dateToIndices;

    FenwickTree distanceTree;
    FenwickTree timeTree;

    int nextIndex;
    int nextActivityId;
    
    vector<int> getIndicesInRange(const tm& start, const tm& end) const;

public:
    AthleteTracker(const string& name, int capacity); //Constructor
    ~AthleteTracker(); //Destructor

    int addActivity(const tm& date, double distance, double time);
    void removeActivity(int activityId); 
    void updateActivity(int activityId, double newDistance, double newTime);
    int getNextActivityId();
    void appendActivityWithoutRebuild(const Activity& a);
    
    double totalDistance() const;
    double totalTime() const;
    double averagePace() const;
    
    tm getOldestDate() const;
    tm getNewestDate() const;
    
    double distanceInRange(const tm& start, const tm& end) const;
    double timeInRange(const tm& start, const tm& end) const;
    double paceInRange(const tm& start, const tm& end) const;

    const string& getName() const;
    const vector<Activity>& getActivities() const;

    string formatDate(const tm& date) const;

    void printFenwickTrees() const;
    void rebuildTrees();

    vector<double> getRawDistances() const;
    vector<double> getRawTimes() const;
};

#endif

 
