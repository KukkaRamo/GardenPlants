#include "pch.h"
#include "PlantTypeInfo.h"

// Default constructor
PlantTypeInfo::PlantTypeInfo()
{
}

// Default destructor
PlantTypeInfo::~PlantTypeInfo()
{
}


// Build user guiding for inserting plants by text command prompt.  First quiding texts, then commands
pair <string, string> PlantTypeInfo::buildTextInsertGuidingPair()
{
	stringstream ss, ss2;
	ss.clear();
	ss2.clear();
	ss2 << "Type: ";
	for (auto item : PlantInfoMap) {
		ss << item.second.getAbbreviation();
		ss2 << " " << item.second.getAbbreviation() << " = " << item.second.getDescription();
	}
	ss << 'q';
	ss2 << " q = quit ";
	return pair<string, string>(ss2.str(), ss.str());
}

// Fetches a plant type corresponding a specific user command
// Returns PLANTTYPE::UNDEFINED if the type does not exist
PLANTTYPE PlantTypeInfo::userCharToPlantType(char pInputChar) {
	PLANTTYPE myType = PLANTTYPE::UNDEFINED;
	for (auto item : PlantInfoMap)
		if (item.second.getAbbreviation() == pInputChar) {
			myType = item.first;
		}
	return myType;
}

// Fetches a user command corresponding a specific plant type,
// Returns the blank character if the type does not exist
char PlantTypeInfo::plantTypeToUserChar(PLANTTYPE pType) {
	if (PlantInfoMap.find(pType) == PlantInfoMap.end()) {
		return ' ';
	}
	else
		return PlantInfoMap.at(pType).getAbbreviation();
}
