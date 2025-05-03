#include "menuFunctions.h"
#include "Activity.h"
#include "AthleteTracker.h"
#include "FenwickTree.h"
#include "CSVProc.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

void viewSummary(map<string, AthleteTracker*>& athletes){
    if (athletes.empty()){
        cout<<"No data available"<<endl<<endl;
    }
    else {
        for (const auto& [name, tracker] : athletes) {
            cout << "Athlete: " << name << endl;
            cout << "  Total Distance: " << tracker->totalDistance() << " miles" << endl;
            cout << "  Total Time: " << tracker->totalTime() << " minutes" << endl;
            cout << "  Average Pace: " << tracker->averagePace() << " min/mile" << endl;
            cout << "Oldest activity date: " << tracker->formatDate(tracker->getOldestDate()) << endl;
            cout << "Newest activity date: " << tracker->formatDate(tracker->getNewestDate()) << endl;
            cout << endl<<endl;
        }
    }
}

void importCSVMenu(map<string,AthleteTracker*>& athletes) {
    string yesno="";
    cout<<"please ensure your csv file is in the csv_files folder." <<endl<<"Is your file in csv_files folder? (Y/N)?"<<endl;
    cin>>yesno;

    if (yesno=="Y" || yesno=="y"){
        string filename="";
        cout<<"Please enter the file name, including .csv extension: "<<endl;
        cin>>filename;
        string fullpath="csv_files/"+filename;
                
        //check if file exists in folder
        ifstream testfile(fullpath);
        if (!testfile.is_open()){
            cout<<"Error. File name not found in csv_file folder."<<endl<<endl;
        }
        else {
            testfile.close();
                
            CSVProc::importCSV(fullpath, athletes, 100);  // capacity = 100 entries per athlete
            cout<<"Successfully imported csv"<<endl<<endl;
        }
    }
    else {
        cout<<"Exiting procedure. Please paste csv in correct folder and re-run program."<<endl<<endl;
        exit(0);
    }
}   


void removeActivityMenu(map<string, AthleteTracker*>& athletes) {
    string athletename;
    cout << "Enter athlete name: ";
    cin >> athletename;
    cout << endl;

    if (athletes.find(athletename) == athletes.end()) {
        cout << "Athlete not found." << endl << endl;
    }

    else {
        //all activities
        const vector<Activity>& activities = athletes[athletename]->getActivities();

        cout << "Would you like to:" << endl;
        cout << "1. Enter date to remove now" << endl;
        cout << "2. List all activities for this athlete first" << endl;
        cout << "Enter 1 or 2: ";

        int subchoice;
        cin >> subchoice;
        cout << endl;

        if (subchoice == 2) {
            if (activities.empty()) {
                cout << "No activities recorded for this athlete." << endl << endl;
            }
            else {
                //list all activities for that athlete
                cout << "Activities for " << athletename << ":" << endl;
                for (const auto& activity : activities) {
                    cout << "  Date: " << athletes[athletename]->formatDate(activity.date)
                        << ", Distance: " << activity.distance
                        << " miles, Time: " << activity.time << " minutes" << endl;
                }
                cout << endl;
            }
        }

        // Now ask for the date to remove
        string dateStr;
        cout << "Enter activity date to remove (MM/DD/YYYY): ";
        cin >> dateStr;
        cout << endl;

        tm date = CSVProc::parseDate(dateStr);

        // find activity ID matching the given date
        bool found = false;
        int foundId = -1;

        for (const auto& activity : activities) {
            if (activity.date.tm_year == date.tm_year &&
                activity.date.tm_mon == date.tm_mon &&
                activity.date.tm_mday == date.tm_mday) {
                found = true;
                foundId = activity.id;
                break;
            }
        }
        

        if (found) {
            athletes[athletename]->removeActivity(foundId);
            cout << "Activity removed." << endl << endl;
        }
        else {
            cout << "No activity found on that date." << endl << endl;
        }
    }
}


void addActivityMenu(map<string, AthleteTracker*>& athletes) {
    string athletename="";
    cout<<"Enter athlete name: ";
    cin>>athletename;
    cout<<endl;

    string dateStr;
    cout<<"Enter activity date in format MM/DD/YYYY: ";
    cin>>dateStr;
    cout<<endl;

    double distance=0;
    cout<<"Enter activity distance in miles: ";
    cin>>distance;
    cout<<endl;

    double time=0;
    cout<<"Enter the time in minutes: ";
    cin>>time;
    cout<<endl;
    tm date = CSVProc::parseDate(dateStr);

    if (athletes.find(athletename)==athletes.end()){
        athletes[athletename]= new AthleteTracker(athletename,100); //100 is default capacity
    }

    athletes[athletename]->addActivity(date,distance,time);
    cout<<"Activity added successfully"<<endl;

}


void editActivityMenu(map<string, AthleteTracker*>& athletes){
    string athletename;
    cout << "Enter athlete name: ";
    cin >> athletename;
    cout << endl;

    if (athletes.find(athletename) == athletes.end()) {
        cout << "Athlete not found." << endl << endl;
    }
    else {
        const vector<Activity>& activities = athletes[athletename]->getActivities();

        cout << "Would you like to:" << endl;
        cout << "1. Enter date to edit now" << endl;
        cout << "2. List all activities for this athlete first" << endl;
        cout << "Enter 1 or 2: ";

        int subchoice;
        cin >> subchoice;
        cout << endl;

        if (subchoice == 2) {
            if (activities.empty()) {
                cout << "No activities recorded for this athlete." << endl << endl;
            }
            else {
                cout << "Activities for " << athletename << ":" << endl;
                for (const auto& activity : activities) {
                    cout << "  Date: " << athletes[athletename]->formatDate(activity.date)
                            << ", Distance: " << activity.distance
                        << " miles, Time: " << activity.time << " minutes" << endl;
                }
                cout << endl;
            }
        }

        // Now ask for the date to edit
        string dateStr;
        cout << "Enter activity date to edit (MM/DD/YYYY): ";
        cin >> dateStr;
        cout << endl;

        tm date = CSVProc::parseDate(dateStr);

        bool found = false;
        int foundId = -1;
        double oldDistance = 0.0;
        double oldTime = 0.0;

        for (const auto& activity : activities) {
            if (activity.date.tm_year == date.tm_year &&
                activity.date.tm_mon == date.tm_mon &&
                activity.date.tm_mday == date.tm_mday) {
                found = true;
                foundId = activity.id;
                oldDistance = activity.distance;
                oldTime = activity.time;
                break;
            }
        }

        if (found) {
            double newDistance;
            cout << "Enter new distance (in miles): ";
            cin >> newDistance;
            cout << endl;

            double newTime;
            cout << "Enter new time (in minutes): ";
            cin >> newTime;
            cout << endl;

            // Update the activity
            athletes[athletename]->updateActivity(foundId, newDistance, newTime);
            cout << "Activity updated successfully." << endl << endl;
        }
        else {
            cout << "No activity found on that date." << endl << endl;
        }
    }
}

void printFenwickTreesMenu(map<string, AthleteTracker*>& athletes) {
    if (athletes.empty()) {
        cout << "No athlete data available yet." << endl << endl;
    }

    int choice;
    cout<<"Do you want to:"<<endl;
    cout<<"1. Print Fenwick Trees for all athletes"<<endl;
    cout<<"2. Print Fenwick Trees for a single athlete"<<endl<<endl;
    cin>>choice;

    if (choice==1){
        for (const auto& [name, tracker] : athletes) {
            cout << "Athlete: " <<name<<endl;
            tracker->printFenwickTrees();
            cout<<endl<<endl;
        }
    }
    else if (choice==2){
        string name;
        cout<<"Enter athlete name: ";
        cin>>name;

        auto it=athletes.find(name);
        if (it != athletes.end()){
            cout<<"Athlete: "<<name<<endl;
            it->second->printFenwickTrees();

        }

        else{
            cout<<"Athlete not found"<<endl;
        }
    }

    else {
        cout<<"Invalid choice. Enter 1 or 2."<<endl;
    }

}

void viewSummaryByRange(map<string, AthleteTracker*>& athletes) {
    if (athletes.empty()) {
        cout << "No athlete data available." << endl;
        return;
    }

    string startStr, endStr;
    cout << "Enter start date (MM/DD/YYYY): ";
    cin >> startStr;
    cout << "Enter end date (MM/DD/YYYY): ";
    cin >> endStr;

    tm start = CSVProc::parseDate(startStr);
    tm end = CSVProc::parseDate(endStr);

    for (const auto& [name, tracker] : athletes) {
        cout << "Athlete: " << name << endl;
        cout << "  Distance (in range): " << tracker->distanceInRange(start, end) << " miles" << endl;
        cout << "  Time (in range): " << tracker->timeInRange(start, end) << " minutes" << endl;
        cout << "  Average Pace (in range): " << tracker->paceInRange(start, end) << " min/mile" << endl;
        cout << endl;
    }
}


