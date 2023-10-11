#include "interest.h"

enum class Room {
	A = 0,
	B = 1
};

class Person: public Interest {
	private:
		int ID;
		std::string interest;
		Room location;
	
	public:
		Person(const int &ID, const int &interestIndex); // Constructor
		int getID() const; // Get the ID of the person
		std::string getInterest() const; // Get the interest of the person
		void showDetails() const;	// Show the ID, interest, and location of a person
		std::string inquireInterest(const Person &otherPerson) const; // Inquire the interest of another person
		void changeRoom(); // Move the person from Room A to Room B
};

