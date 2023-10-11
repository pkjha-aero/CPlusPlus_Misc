#include <iostream>
#include <string>
#include <vector>
	
class Interest {
	private:
		std::vector<std::string> interests; // All possible interests
	public:
		Interest(); //Constructor, populate all the possible interests
		
		// Pick a random interest index and assign the corresponding interest 
		std::string assignInterest(const int &interestIndex) const;
};

