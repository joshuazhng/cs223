/* 
 * Station.cpp
 * Joshua Zhang
 * CPSC 223 PSET 4
 * 4/6/23
 * Implementation of the Station class
 */

#include "Station.h"

// Constructor
Station::Station(){
	name = "NoName";
    access = false;
}

// Parameterized Constructor
Station::Station(string input_name, bool input_access){
    name = input_name;
    access = input_access;
}

// Function: isEqual
// Input: another Station, s
// Returns: returns true if both stations have the same name and accessibility, false if not
// Does: checks if the station s is equal to the station whose function is being invoked
bool Station::isEqual(Station s){
    return(name == s.getName() && access == s.getAccess());
}

// Function: print
// Input: takes in a reference to an ostream object
// Returns: void
// Does: print the string containing the station name and an A or U 
//       to indicate whether accessibility options are available
void Station::print(ostream &outfile){
    outfile << name << (access? " A" : " U");
}


