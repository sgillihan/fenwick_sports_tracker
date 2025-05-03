#ifndef MENUFUNCTIONS_H__
#define MENUFUNCTIONS_H__

#include <map>
#include <string>
#include "AthleteTracker.h"

using namespace std;

// The Menu Functions provide a user interface, allowing the user to perform different operations from a menu
// User choices and input are processed and the corresponding functions are called and executed.

// The function titles are fairly self explanatory

void viewSummary(map<string, AthleteTracker*>& athletes);
void importCSVMenu(map<string, AthleteTracker*>& athletes);
void removeActivityMenu(map<string, AthleteTracker*>& athletes);
void addActivityMenu(map<string, AthleteTracker*>& athletes);
void editActivityMenu(map<string, AthleteTracker*>& athletes);
void printFenwickTreesMenu(map<string, AthleteTracker*>& athletes);
void viewSummaryByRange(map<string, AthleteTracker*>& athletes);

#endif
