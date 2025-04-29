#include <iostream>
#include <fstream>
#include <map>
#include "../code/Activity.h"
#include "../code/AthleteTracker.h"
#include "../code/FenwickTree.h"
#include "../code/CSVProc.h"
#include "../code/menuFunctions.h"

using namespace std;

int main() {
    int choice=-1;
    map<string, AthleteTracker*> athletes;

    cout<<"Welcome to the S. Gillihan Fenwick Tree Sports Tracker"<<endl;

    while (choice != 0){
        cout<<"Please choose an option from the menu below (enter integer):"<<endl;
        cout<<"1. View current athlete data summary"<<endl;
        cout<<"2. Import new data from csv"<<endl;
        cout<<"3. Remove an activity"<<endl;
        cout<<"4. Add an activity"<<endl;
        cout<<"5. Edit an activity"<<endl;
        cout<<"6. Print current Fenwick Trees"<<endl;
        cout<<"0. Exit program"<<endl<<endl;
        cout<<"Your choice: ";

        cin>>choice;

        cout<<endl<<endl;

        if (choice == 1) {
            viewSummary(athletes);
        } 
        else if (choice == 2) {
            importCSVMenu(athletes);
        } 
        else if (choice == 3) {
            removeActivityMenu(athletes);
        } 
        else if (choice == 4) {
            addActivityMenu(athletes);
        } 
        else if (choice == 5) {
            editActivityMenu(athletes);
        } 
        else if (choice == 6) {
            printFenwickTreesMenu(athletes);
        } 
        else if (choice != 0) {
            cout << "Invalid option." << endl<<endl;
        }
    }

    // Deallocate trackers
    for (auto& [name, tracker] : athletes) {
        delete tracker;
    }
    cout<<"Exiting program."<<endl<<endl;
    return 0;
}