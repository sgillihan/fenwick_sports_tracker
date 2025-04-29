#ifndef MENUFUNCTIONS_H__
#define MENUFUNCTIONS_H__

#include <map>
#include <string>
#include "AthleteTracker.h"

using namespace std;

void viewSummary(map<string, AthleteTracker*>& athletes);
void importCSVMenu(map<string, AthleteTracker*>& athletes);
void removeActivityMenu(map<string, AthleteTracker*>& athletes);
void addActivityMenu(map<string, AthleteTracker*>& athletes);
void editActivityMenu(map<string, AthleteTracker*>& athletes);
void printFenwickTreesMenu(map<string, AthleteTracker*>& athletes);
void viewSummaryByRange(map<string, AthleteTracker*>& athletes);

#endif
