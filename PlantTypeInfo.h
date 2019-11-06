#pragma once
#include "Plant.h"
#include <map>
#include <string>

using namespace std;

class PlantTypeInfo
{
public:
	class PlantTypeData {
	public:
		// Constructor
		PlantTypeData(string pClassName, char pAbbreviation, string pDescription)
			: ClassName(pClassName), Abbreviation(pAbbreviation), Description(pDescription) {}

		// Getter for abbreviation
		char getAbbreviation() {
			return Abbreviation;
		}

		// Getter for description
		string getDescription() {
			return Description;
		}

	private:
		const string ClassName;
		const char Abbreviation;
		const string Description;
	};

	PlantTypeInfo();
	~PlantTypeInfo();

	static pair <string, string> buildTextInsertGuidingPair();
	static PLANTTYPE userCharToPlantType(char pInputChar);
	static char plantTypeToUserChar(PLANTTYPE pType);
	
};

static map<PLANTTYPE, PlantTypeInfo::PlantTypeData> PlantInfoMap {
	{PLANTTYPE::BASIC, PlantTypeInfo::PlantTypeData("Plant", 'b', "Basic plant")},
	{ PLANTTYPE::DECORATION, PlantTypeInfo::PlantTypeData("DecorationPlant",'d',"Decoration plant") },
	{ PLANTTYPE::UTILITY, PlantTypeInfo::PlantTypeData("UtilityPlant",'u',"Utility plant") }
};

