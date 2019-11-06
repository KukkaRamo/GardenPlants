#include "pch.h"
#include "PlantFactory.h"

// Default constructor
PlantFactory::PlantFactory()
{
}

// Default destructor
PlantFactory::~PlantFactory()
{
}

// Creates plant with specific id and type, 
// or returns nullptr if the creation has been cancelled or the type is unknown
shared_ptr<Plant> PlantFactory::buildPlantFromType(const int pid, const PLANTTYPE pPlantType) {
	bool cancel { false };
	shared_ptr<Plant> p;
	if (pPlantType == PLANTTYPE::UTILITY) {
		p = make_shared<UtilityPlant>(UtilityPlant(pid, cancel));
	}
	else if (pPlantType == PLANTTYPE::DECORATION) {
		p = make_shared<DecorationPlant>(DecorationPlant(pid, cancel));
	}
	else if (pPlantType == PLANTTYPE::BASIC) {
		p = make_shared<Plant>(Plant(pid, cancel));
	}
	else p = nullptr;
	if (cancel) {
		return nullptr;
	}
	else return p;
}

// Creates plant with specific type (input as user char) and reads ID from the stream
// Returns nullptr if the type is unknown
shared_ptr<Plant> PlantFactory::buildPlantFromTypeCharAndStream(istringstream& iss, const char FieldSeparator, const char pPlantTypeChar) {
	PLANTTYPE myType = PlantTypeInfo::userCharToPlantType(pPlantTypeChar);
	if (myType == PLANTTYPE::UTILITY) {
		return make_shared<UtilityPlant>(UtilityPlant(iss, FieldSeparator));
	}
	else if (myType == PLANTTYPE::DECORATION) {
		return make_shared<DecorationPlant> (DecorationPlant(iss, FieldSeparator));
	}
	else if (myType == PLANTTYPE::BASIC) {
		return make_shared<Plant> (Plant(iss, FieldSeparator)); // Let us assume that we never want more details for basic plant
	}
	else return nullptr;
}


// Creates plant with specific id and desired type based on user command,
// or returns nullptr if the creation has been cancelled or the type is unknown
shared_ptr<Plant> PlantFactory::buildPlantFromUser(const int pid, const char pPlantTypeChar) {
	return buildPlantFromType(pid, PlantTypeInfo::userCharToPlantType(pPlantTypeChar));
}
