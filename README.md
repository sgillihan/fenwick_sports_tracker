# Sports Performance Using Fenwick Trees (Final Project)
## CSPB 2270 Spring 2025
## Stephanie Gillihan

## Fenwick Tree Background 

Fenwick Trees, also known as Binary Indexed Trees, were named after Peter Fenwick when he introduced the concept in 1994. Fenwick Trees are highly efficient for tasks such as calculating cumulative sums over a range and dynamically updating values for specific data points. 

The key to Fenwick Trees is the concept that every number can be represented in binary form. Fenwick Trees use the last set bit, or the least significant bit, in each index to determine a range of values over which the cumulative sum will be calculated and stored. These partial sums are stored in the tree structure. 

When a query for a sum over a range is made, the Fenwick Tree does not have to access each index in the range. Instead, it uses the stored partial sums to quickly jump through indices and return the total in O(log n) time.

## Project Proposal and Scope
### Modified from Original Submission

For my CSPB 2270 final project, I plan to use a Fenwick Tree to implement a sports performance tracker. I am interested in using my computer science degree to pursue a career in data science, data analytics, or data architecture, so a project that focuses on analytics seems like a good choice. Tracking training metrics is a project of personal interest for me, because I like to train for triathlons, running races, and cycling events. I have gathered anonymized running/walking/hiking data from myself and friends to demonstrate how the Fenwick Tree data structure handles cumulative sums, added/removed data, and data updates to allow for instant updates. 

## Functionality of Project
### Modified from Original Project Proposal

* Allow user to import csv file with appropriate headers: Name, Date, Distance, Time
* Process the csv to store the data
* Update existing Fenwick Trees with the new data, or create a new tree if a new name is introduced
* Add activity entries manually one by one if desired
* Remove an entry if desired
* Correct data values if an incorrect value occurs
* Return query values such as
  * Cumulative miles per athlete (all-time)
  *	Cumulative time (all-time)
  * Cumulative average pace per athlete (all-time)
  *	Total miles from mm/dd/yyyy to mm/dd/yyyy for Athlete A
  *	Total time from mm/dd/yyyy to mm/dd/yyyy for Athlete A
  *	Average pace from mm/dd/yyyy to mm/dd/yyyy for Athlete A
  *	Given time period mm/dd/yyyy to mm/dd/yyyy, provide mileage leader, time leader, and average pace leader out of existing athletes
* Visualize how the Fenwick Tree works using the Print Fenwick Tree tool

## Compiling and Running

When the project repository is cloned to a local or Jupyter environment, compile the project in the appropriate location using terminal commands. The compiler looks in the app folder for main.cpp and the code folder for all of the .h and .cpp files. It places the run file in the /bin folder. 

Example: [*your location directory here*]$ g++ app/main.cpp code/*.cpp -o bin/fenwick_tracker

Run the program from the terminal using command: ./bin/fenwick_tracker

## References

Carpanese, Igor. "A Visual Introduction to Fenwick Tree." Medium, May 16, 2021, [Visual Intro to Fenwick Tree](medium.com/carpanese/a-visual-introduction-to-fenwick-tree-89b82cac5b3c).

"boba5551". "Binary Indexed Trees." TopCoder, October 31, 2018, [TopCoder Binary Indexed Trees](topcoder.com/thrive/articles/Binary%20Indexed%20Trees).





