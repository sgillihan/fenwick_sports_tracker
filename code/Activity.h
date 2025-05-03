#ifndef ACTIVITY_H__
#define ACTIVITY_H__

#include <ctime>
#include <string>

using namespace std;

// The activity structure supports the format the data
// will be imported in: Name, Date, Distance, and Time.
// Additionally, an id will be assigned to each activity
// instance. 

struct Activity {
  int id;
  string name;
  tm date;
  double distance; // distance in miles
  double time; // time in minutes

};

#endif