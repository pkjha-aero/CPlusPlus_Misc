#include "utilFunc.h" // This includes "person.h"

#include <chrono>
#include <thread>
#include <stdexcept>

int main(int argc, char** argv) {
	int N, ID1, ID2, index1, index2, T;
	const int numInterests = 4; // Fixed for this case, but need not be in general
	
	// Get the number of persons as input
    std::cout << "How many persons are there in the party?" << std::endl;
    std::cin >> N;
    std::cout << "There are " << N << " persons in the party" << std::endl << std::endl; 
    if ( N >  INT8_MAX ) {
    	std::cout << "INT_MAX = " << INT8_MAX << std::endl;
        throw std::invalid_argument("Number of persons should be at the most INT_MAX");
    }
    
    // Get the number of time steps as input
    std::cout << "What is the maximum number of time steps allowed in the simulation?" << std::endl;
    std::cin >> T;
    std::cout << "The max number of time steps is: " << T << std::endl << std::endl;
    
    // Create lists in rooms A and B
	std::cout << "Creating a list of persons in rooms A and B ... \n";
	std::list<Person> personsInRoomA = createPersonList(N, numInterests);
	std::list<Person> personsInRoomB; // Empty
		
	// Show the lists
	std::cout << "Showing the complete list of persons created in the beginning... \n";
	std::cout << "... Room A ... " << std::endl;
	showPersonList(personsInRoomA);
	std::cout << "... Room B ... " << std::endl;
	showPersonList(personsInRoomB);
	
	// Start the time loop
	srand(time(NULL)); // seed for random number
	std::cout << std::endl << "########## Starting the simulation ############" << std::endl << std::endl;
	int timeStep = 0;
	while (timeStep < T) {
		std::cout << "*** Time step: " << timeStep << " ************************* "  << std::endl;
		
		// Check if there are at least two persons in room A
		if (personsInRoomA.size() < 2) {
			std::cout << "Left with " << personsInRoomA.size() << " persons in room A." << std::endl
					  << " Need at least two to continue. Stopping the simulation." << std::endl;
			break;
		}
		
		// Select two random persons if there are at least two in room A
		index1 = rand()%personsInRoomA.size();
		index2 = rand()%personsInRoomA.size();
		std::cout << "index 1: " << index1 << ", index 2: " << index2 << std::endl;
		// Check if we need to or should go to the next time step
		if (index1 == index2){
			std::cout << "Two persons selected randomly are at the same indices. So, an interaction is not possible." << std::endl
			          << "Selecting another pair at this time step." << std::endl << std::endl;
			continue; // Don't increase the time step
		}
		
		//auto it1 = std::next(personsInRoomA.begin(), index1);
		//auto it2 = std::next(personsInRoomA.begin(), index2);
		ID1 = std::next(personsInRoomA.begin(), index1)->getID();
		ID2 = std::next(personsInRoomA.begin(), index2)->getID();
		std::cout << "Two persons selected randomly have their IDs: "<< ID1 << " and " << ID2 << std::endl;
			
		// Interaction between two persons with some IDs
		auto match = interact(ID1, ID2, personsInRoomA, personsInRoomB);
		if (personsInRoomA.size() == 2 && !match) {
			std::cout << "Left with just " << personsInRoomA.size() << " persons in room A" << std::endl
					  << " They do not match. Stopping the simulation." << std::endl;
			break;
		}
		
		// Print the internal state
		printInternalState(personsInRoomA, personsInRoomB);
		
		// Given an 'ID', print the person's interest and location
		// printInterestAndLocation(ID1, personsInRoomA);
		
		// Pause for a designated time
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		
		// Go to next step
		timeStep++;
	} // end while loop
	
}// end main
