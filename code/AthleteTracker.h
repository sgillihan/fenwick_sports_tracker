#ifndef ATHLETETRACKER_H__
#define ATHLETETRACKER_H__

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include "FenwickTree.h"
#include "Activity.h"

using namespace std;

// The AthleteTracker class defines how the imported or added data is stored in Fenwick Trees for each athlete.
// This class defines and manages the different analytics available for stored data
// This class also defines operations for adding, editing, and removing Activity data 

// Private members are used only within the class, and public members are used by other functions and files.

class AthleteTracker {
private:
    string athleteName;
    
    //vector<Activity> activities is the list of activities maintained for each athlete
    //Activities are stored in chronological date order
    //The Fenwick trees are built from activities and rebuilt if there is added data
    vector<Activity> activities;

    map<int, int> idToIndexMap; // maps unique activity ID to tree index
    // map<int, int> indexToIdMap; // reverse ID lookup- not currently in use
    map<string,vector<int>> dateToIndices; // formatted date, associated tree index

    // Separate Fenwick Trees for cumulative time and distance
    FenwickTree distanceTree;
    FenwickTree timeTree;

    // internal indexing operations
    int nextIndex;
    int nextActivityId;

    // This member allows user input date ranges to be translated to the correct indices within the tree
    // This is required for querying within a specific date range
    vector<int> getIndicesInRange(const tm& start, const tm& end) const;

public:
    AthleteTracker(const string& name, int capacity); //Constructor
    //~AthleteTracker(); //Destructor- not needed due to use of vector

    // This function allows for all records in a csv file to be added to Activities one by one before the tree is built
    // the tree is built after all records are appended
    void appendActivityWithoutRebuild(const Activity& a);

    // Add activity allows the user to add a single activity to the Activities class
    // The Fenwick Trees are rebuilt after the addition
    int addActivity(const tm& date, double distance, double time);

    // Remove activity allows the user to delete a single activity.
    // The Fenwick Trees are rebuilt after the removal
    void removeActivity(int activityId);

    // Update activity allows the user to update the time or distance for a specific date that already exists
    // The Fenwick Trees are rebuilt after the update
    void updateActivity(int activityId, double newDistance, double newTime);

    // internal indexing operations
    int getNextActivityId();
    
    // Defines cumulative statistics to be reported
    double totalDistance() const;
    double totalTime() const;
    double averagePace() const;
    
    // Defines oldest and newest dates in record for each athlete- for user information
    tm getOldestDate() const;
    tm getNewestDate() const;
    
    // Defines cumulative statistics for a certain date range defined by the user
    double distanceInRange(const tm& start, const tm& end) const;
    double timeInRange(const tm& start, const tm& end) const;
    double paceInRange(const tm& start, const tm& end) const;

    // Get athlete name from Activities
    const string& getName() const;

    // This provides a read only reference to the list of activities
    const vector<Activity>& getActivities() const;

    // Format Date from Activities for appropriate use in trees (YYYY-MM-DD)
    string formatDate(const tm& date) const;

    // The print Fenwick Trees function is the primary method of illustrating the inner workings of a Fenwick Tree
    // Raw values, tree nodes, and cumulative query paths are all printed.
    // Print Fenwick Tree allows the user to see how the cumulative sums are stored over large amounts of data,
    // and allows the user to see how the query operation jumps through different indices to access cumulative sums in
    // O(log n) time
    // This function essentially calls the primary function from the FenwickTree.cpp
    void printFenwickTrees() const;

    // Rebuild Trees clears existing Fenwick Trees and rebuilds them when activities are modified.
    void rebuildTrees();

    // These functions support print Fenwick Trees
    vector<double> getRawDistances() const;
    vector<double> getRawTimes() const;
};

#endif

 
