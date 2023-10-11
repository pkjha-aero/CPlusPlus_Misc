#include "person.h"
	
Person::Person(const int &ID, const int &interestIndex) : 
	Interest(), ID(ID), interest(assignInterest(interestIndex)), location(Room::A) {
		// Assign the ID and interest (based on random interest index)
		// By default, have the person created remain in Room A
}

int Person::getID() const {
	return ID;
}

std::string Person::getInterest() const {
	return interest;
}

void Person::showDetails() const {
	std::cout <<"Person's ID: " << ID << ", Interest: " << interest << ", Location: ";
	switch(location) {
		case Room::A:
			std::cout << "Room A";
			break;
		case Room::B:
			std::cout << "Room B";
	}
	std::cout << std::endl;
}

std::string Person::inquireInterest(const Person &otherPerson) const{
	return otherPerson.getInterest();
}

void Person::changeRoom() {
	if (location == Room::A)
		location = Room::B;
	else
		std::cout << " Person with ID " << ID << " is already in room B. Nothing to do!" << std::endl;;	
}

