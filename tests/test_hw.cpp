#include <iostream>
#include <map>
#include "AthleteTracker.h"
#include "CSVProc.h"

using namespace std;

int tests() {
    map<string, AthleteTracker*> athletes;

    string filename = "Test_Data_1.csv";
    CSVProc::importCSV(filename, athletes, 100);  // capacity = 100 entries per athlete

    for (const auto& [name, tracker] : athletes) {
        cout << "Athlete: " << name << endl;
        cout << "  Total Distance: " << tracker->totalDistance() << " miles" << endl;
        cout << "  Total Time: " << tracker->totalTime() << " minutes" << endl;
        cout << "  Average Pace: " << tracker->averagePace() << " min/mile" << endl;
        cout << endl;
    }

    // Cleanup: deallocate all trackers
    for (auto& [name, tracker] : athletes) {
        delete tracker;
    }

    return 0;
}