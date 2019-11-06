#pragma once
#include "Plant.h"
#include "DecorationPlant.h"
#include "PlantTypeInfo.h"
#include "UtilityPlant.h"
#include <map>
#include <iostream>
#include <string>

class PlantFactory {
public:
	PlantFactory();
	~PlantFactory();

	static shared_ptr<Plant> buildPlantFromType(const int pid, const PLANTTYPE pPlantType);
	static shared_ptr<Plant> buildPlantFromTypeCharAndStream(istringstream& iss, const char FieldSeparator, const char pPlantType);
	static shared_ptr<Plant> buildPlantFromUser(const int pid, const char pInputChar);
};

