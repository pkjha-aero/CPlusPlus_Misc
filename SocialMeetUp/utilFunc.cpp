#include "utilFunc.h"

// Create a list of N persons with random interests
std::list<Person> createPersonList(const int &N, const int &numInterests) {
	std::list<Person> personList;
	
	srand(time(NULL)); // seed for random number
	for (int ID=0; ID<N; ID++){
		int interestIndex = rand()%numInterests;
		//std::cout <<"Person's ID: " << ID << ", Interest Index: " << interestIndex << std::endl;
		Person p(ID, interestIndex);	
		personList.push_back(p);
	}
	return personList;
}

// Show the details of persons in a list, i.e., in a room
void showPersonList(std::list<Person> &personList) {
	//std::cout << "Size of the list: "<< personList.size() << std::endl;
	if (!personList.empty()){
//		for (std::list<Person>::iterator it=personList.begin(); it!=personList.end(); ++it)
//			it->showDetails();
		for (auto &pers : personList)
			pers.showDetails();
	}
	else {
		std::cout <<"The list is empty" << std::endl;
	}
}

// Print internal state, i.e., who is in which room etc.
void printInternalState(std::list<Person> &personListA, std::list<Person> &personListB) {
	std::cout << "IDs of persons in Room A: " << std::endl;
	for (auto &pers : personListA) {
		std::cout << pers.getID() << " ";
	}
	std::cout << std::endl;
	
	std::cout << "IDs of persons in Room B: " << std::endl;
	for (auto &pers : personListB) {
		std::cout << pers.getID() << " ";
	}
	std::cout << std::endl;
}

// Given an 'ID', search for a person with that ID in a list of persons
std::list<Person>::iterator searchIDInAPersonList(const int &ID, std::list<Person> &personList) {
	std::list<Person>::iterator it = std::find_if( personList.begin(), personList.end(),
                            [&](const Person &pers ){ return pers.getID()==ID; } );
                            
    if ( personList.end() == it ){
        std::cout << "ID (" << ID << " ) doesn't belong to any person in the list" << std::endl;
    }
    return it;
}

// Given an 'ID', print the person's interest and location
void printInterestAndLocation(const int &ID, std::list<Person> &personList) {
	auto it = searchIDInAPersonList(ID, personList);
	if (it != personList.end()) {
        const int pos = std::distance( personList.begin(), it );
        std::cout << "Person with given ID (" << ID << " ) found at position " << pos << std::endl;
        it->showDetails();
    }
}

// Interaction between two persons
bool interact(const int &ID1, const int &ID2, std::list<Person> &personListA, std::list<Person> &personListB) {
    bool match = false;
	// Get the iterators of persons with IDs 'ID1' and 'ID2'
	auto it1 = searchIDInAPersonList(ID1, personListA);
	auto it2 = searchIDInAPersonList(ID2, personListA);
	// Check if both the IDs are found in the list of persons in room A
	if(it1 != personListA.end() && it2 != personListA.end()) {
		std::cout << "Person 1 has ID (" << ID1 << " ) and interest ( " 
		          << it1->getInterest() << " )" << std::endl;
		std::cout << "Upon inquiring, it was known to person 1 that person 2 with ID (" 
		          << ID2 << " ) has an interest (" << it1->inquireInterest(*it2)<<" )" << std::endl;
		
		// Check if their interests match
		if (it1->getInterest() == it1->inquireInterest(*it2)){
			std::cout << "The two persons have a common interest and will move to Room B" << std::endl;
			// Change the room of the persons
			it1->changeRoom();
			it2->changeRoom();
			// Move to Room B
			personListB.push_back(*it1);
			personListB.push_back(*it2);
			// Remove from Room A
			personListA.erase(it1);	
			personListA.erase(it2);
			match = true;
		}
		else {
			std::cout << "The two persons don't have a common interest and will remain in Room A" << std::endl;
		}
	}
	return match;
}



