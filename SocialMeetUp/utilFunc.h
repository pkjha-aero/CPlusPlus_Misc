#include "person.h"

#include <algorithm> // for std::find_if
#include <list>
#include <ctime>
#include <cstdlib>

// Create a list of N persons with random interests
std::list<Person> createPersonList(const int &N, const int &numInterests);

// Show the details of persons in a list, i.e., in a room
void showPersonList(std::list<Person> &personList);

// Print internal state, i.e., who is in which room etc.
void printInternalState(std::list<Person> &personListA, std::list<Person> &personListB);

// Given an 'ID', search for a person with that ID in a list of persons
std::list<Person>::iterator searchIDInAPersonList(const int &ID, std::list<Person> &personList);

// Given an 'ID', print the person's interest and location
void printInterestAndLocation(const int &ID, std::list<Person> &personList);

// Interaction between two persons
bool interact(const int &ID1, const int &ID2, std::list<Person> &personListA, std::list<Person> &personListB);

