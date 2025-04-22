# Sports Performance Using Fenwick Trees

## Overview 

A Fenwick Tree's strength is prefix sums, or cumulative sums



## Goals

* Allow user to import csv file with appropriate headers
* Process the csv to store the data
* Update existing Fenwick Trees with the new data, or create a new tree if a new name is introduced
* Add activity entries manually one by one if desired
* Remove an entry if desired
* Return query values such as
  * Cumulative miles per athlete (all-time)
  *	Cumulative time (all-time)
  * Cumulative average pace per athlete (all-time)
  *	Total miles from mm/dd/yyyy to mm/dd/yyyy for Athlete A
  *	Total time from mm/dd/yyyy to mm/dd/yyyy for Athlete A
  *	Average pace from mm/dd/yyyy to mm/dd/yyyy for Athlete A
  *	Given time period mm/dd/yyyy to mm/dd/yyyy, provide mileage leader, time leader, and average pace leader out of existing athletes
* Correct data values if an incorrect value occurs


Specific functions to be implemented include but are not limited to:
1.	Process/store csv data into Activity data format
2.	Build a new tree from Activity data (probably involves helpers or subroutines)
3.	Insert a data point to Activity data
4.	Remove a data point from Activity data
5.	Update tree for an insertion
6.	Update tree for a removal
7.	Define start date and end date from user input
8.	Find date (index) within tree
9.	Return cumulative sum of range
10.	Average pace calculation
11.	Leader calculation



