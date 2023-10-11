#include "interest.h"

Interest::Interest(){
	interests.push_back("epidemiology");
	interests.push_back("biostatistics");
	interests.push_back("clinical research");
	interests.push_back("health policy");
}

std::string Interest::assignInterest(const int &interestIndex) const {
	return interests[interestIndex];
}

