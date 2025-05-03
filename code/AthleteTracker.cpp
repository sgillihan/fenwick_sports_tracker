#include "AthleteTracker.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

AthleteTracker::AthleteTracker(const string& name, int capacity)
    : athleteName(name), distanceTree(capacity, name + " Distance"), timeTree(capacity, name + " Time"), nextIndex(0), nextActivityId(0) {
}

//AthleteTracker::~AthleteTracker() {
//    // no action needed
//}

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

    //add new activity to private member activities vector
    activities.push_back(a);
    rebuildTrees();

    return a.id;
}

void AthleteTracker::removeActivity(int activityId) {
    activities.erase(std::remove_if(activities.begin(), activities.end(), [&](const Activity& a) {
        return a.id == activityId;
    }), activities.end());
    rebuildTrees();
}

void AthleteTracker::updateActivity(int activityId, double newDistance, double newTime) {
    for (auto& a : activities) {
        if (a.id == activityId) {
            a.distance = newDistance;
            a.time = newTime;
            break;
        }
    }
    rebuildTrees();
}

int AthleteTracker::getNextActivityId() {
    return nextActivityId++;
}

void AthleteTracker::appendActivityWithoutRebuild(const Activity& a) {
    activities.push_back(a);
}

double AthleteTracker::totalDistance() const {
    //query fenwick tree on last occupied index
    return distanceTree.query(distanceTree.getSize() - 1);
}

double AthleteTracker::totalTime() const {
    //query fenwick tree on last occupied index
    return timeTree.query(timeTree.getSize() - 1);
}

double AthleteTracker::averagePace() const {
    double t = totalTime();
    double d = totalDistance();
    //calculate pace in minutes per mile
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
    //calculate pace in minutes per mile
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
        // Compare years first using mktime for efficiency
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
        // Compare years first using mktime for efficiency
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

void AthleteTracker::rebuildTrees() {
    // Sort all activities by date
    std::sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        return mktime(const_cast<std::tm*>(&a.date)) < mktime(const_cast<std::tm*>(&b.date));
    });

    // Reset fenwick trees
    distanceTree = FenwickTree(activities.size(), athleteName + " Distance");
    timeTree = FenwickTree(activities.size(), athleteName + " Time");
    idToIndexMap.clear();
    dateToIndices.clear();

    // Reassign tree indices and update trees
    for (int i = 0; i < activities.size(); ++i) {
        const Activity& a = activities[i];
        idToIndexMap[a.id] = i;
        dateToIndices[formatDate(a.date)].push_back(i);
        distanceTree.update(i, a.distance);
        timeTree.update(i, a.time);
    }

    nextIndex = activities.size();
}

