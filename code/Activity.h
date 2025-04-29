#ifndef ACTIVITY_H__
#define ACTIVITY_H__

#include <ctime>
#include <string>

using namespace std;

struct Activity {
  int id;
  string name;
  tm date;
  double distance; // distance in miles
  double time; // time in minutes

};

#endif