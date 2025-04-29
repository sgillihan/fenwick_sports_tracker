#include "AthleteTracker.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

AthleteTracker::AthleteTracker(const string& name, int capacity)
    : athleteName(name), distanceTree(capacity, name + " Distance"), timeTree(capacity, name + " Time"), nextIndex(0), nextActivityId(0) {
}

AthleteTracker::~AthleteTracker() {
    // nothing to delete manually
}

string AthleteTracker::formatDate(const tm& date) const {
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
    return std::string(buffer);
}

int AthleteTracker::addActivity(const tm& date, double distance, double time) {
    //initiate new activity
    Activity a;
    a.id = nextActivityId++;
    a.name = athleteName;
    a.date = date;
    a.distance = distance;
    a.time = time;

    //add new activity to private member activitis vector
    activities.push_back(a);

    //assign the next available index to the activity and map these values for future reference
    int index = nextIndex++;
    idToIndexMap[a.id] = index;
    indexToIdMap[index] = a.id;
    string dateStr = formatDate(date);

    //check if date is already in vector, if not create new vector
    if (dateToIndices.find(dateStr)==dateToIndices.end()){
        dateToIndices[dateStr] = vector<int>();
    }

    //add new activity index to list for appropriate date
    dateToIndices[dateStr].push_back(index);

    //update Time and Distance Fenwick trees
    distanceTree.update(index, distance);
    timeTree.update(index, time);

    return a.id;
}

void AthleteTracker::removeActivity(int activityId) {
    //first check if the activity ID provided exists in the tree. Return early if DNE.
    if (idToIndexMap.find(activityId) == idToIndexMap.end()) return;

    //find Fenwick tree index for provided activity ID
    int index = idToIndexMap[activityId];

    //find the Activity object and essentially deactivate it
    //the time and distance for the deactivated activity are subtracted from Fenwick totals
    for (auto& a : activities) {
        if (a.id == activityId) {
            distanceTree.update(index, -a.distance);
            timeTree.update(index, -a.time);
            break;
        }
    }

    //the activity is still present in activities vector to maintain Fenwick indexing
    //but the mappings are removed to complete deactivation of the activity
    idToIndexMap.erase(activityId);
    indexToIdMap.erase(index);
}

void AthleteTracker::updateActivity(int activityId, double newDistance, double newTime) {
    //first check if the activity ID provided exists in the tree. Return early if DNE.
    if (idToIndexMap.find(activityId) == idToIndexMap.end()) return;
    
    //find Fenwick tree index for provided activity ID
    int index = idToIndexMap[activityId];

    //find the Activity object and update with new values
    //the delta must be calculated, because it's the delta that is added or subtracted from the fenwick tree
    for (auto& a : activities) {
        if (a.id == activityId) {
            //calc deltas
            double deltaDist = newDistance - a.distance;
            double deltaTime = newTime - a.time;

            //update activity vector values
            a.distance = newDistance;
            a.time = newTime;

            //update fenwick trees
            distanceTree.update(index, deltaDist);
            timeTree.update(index, deltaTime);
            break;
        }
    }
}

double AthleteTracker::totalDistance() const {
    return distanceTree.query(distanceTree.getSize() - 1);
}

double AthleteTracker::totalTime() const {
    return timeTree.query(timeTree.getSize() - 1);
}

double AthleteTracker::averagePace() const {
    double t = totalTime();
    double d = totalDistance();
    return (d > 0.0) ? t / d : 0.0;
}

vector<int> AthleteTracker::getIndicesInRange(const tm& start, const tm& end) const {
    vector<int> indices;
    string startStr = formatDate(start);
    string endStr = formatDate(end);

    for (const auto& [dateStr, vec] : dateToIndices) {
        if (dateStr >= startStr && dateStr <= endStr) {
            indices.insert(indices.end(), vec.begin(), vec.end());
        }
    }
    std::sort(indices.begin(), indices.end());
    return indices;
}

double AthleteTracker::distanceInRange(const tm& start, const tm& end) const {
    double sum = 0.0;
    for (int idx : getIndicesInRange(start, end)) {
        sum += distanceTree.rangeQuery(idx, idx);
    }
    return sum;
}

double AthleteTracker::timeInRange(const tm& start, const tm& end) const {
    double sum = 0.0;
    for (int idx : getIndicesInRange(start, end)) {
        sum += timeTree.rangeQuery(idx, idx);
    }
    return sum;
}

double AthleteTracker::paceInRange(const tm& start, const tm& end) const {
    double t = timeInRange(start, end);
    double d = distanceInRange(start, end);
    return (d > 0.0) ? t / d : 0.0;
}

const string& AthleteTracker::getName() const {
    return athleteName;
}

const vector<Activity>& AthleteTracker::getActivities() const {
    return activities;
}

tm AthleteTracker::getOldestDate() const {
    if (activities.empty()) {
        throw runtime_error("No activities available to find oldest date.");
    }

    tm oldest = activities[0].date;

    for (const auto& activity : activities) {
        // Compare years first
        if (mktime(const_cast<tm*>(&activity.date)) < mktime(&oldest)) {
            oldest = activity.date;
        }
    }
    return oldest;
}

tm AthleteTracker::getNewestDate() const {
    if (activities.empty()) {
        throw runtime_error("No activities available to find newest date.");
    }

    tm newest = activities[0].date;

    for (const auto& activity : activities) {
        if (mktime(const_cast<tm*>(&activity.date)) > mktime(&newest)) {
            newest = activity.date;
        }
    }
    return newest;
}

void AthleteTracker::printFenwickTrees() const {
    cout << "\nDistance Tree (" << distanceTree.getName() << "):" << endl;
    vector<double> rawDistances = getRawDistances();
    distanceTree.printFenwickDetails(rawDistances);

    cout << "\nTime Tree (" << timeTree.getName() << "):" << endl;
    vector<double> rawTimes = getRawTimes();
    timeTree.printFenwickDetails(rawTimes);
}

vector<double> AthleteTracker::getRawDistances() const {
    vector<double> rawDistances(nextIndex, 0.0);
    for (const auto& activity : activities) {
        int index = idToIndexMap.at(activity.id);
        rawDistances[index] = activity.distance;
    }
    return rawDistances;
}

vector<double> AthleteTracker::getRawTimes() const {
    vector<double> rawTimes(nextIndex, 0.0);
    for (const auto& activity : activities) {
        int index = idToIndexMap.at(activity.id);
        rawTimes[index] = activity.time;
    }
    return rawTimes;
}

