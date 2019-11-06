#pragma once
#include "Plant.h"

class PlantCollection
{
public:
	PlantCollection();
	virtual ~PlantCollection();

	virtual bool plantExists(const int id) const = 0;
	virtual shared_ptr<Plant> findPlant(const int id) = 0;
	virtual void addPlant(shared_ptr<Plant> const pPlant) = 0;
	virtual void deletePlant(const int id) = 0;
	virtual void updatePlant(const int id, shared_ptr<Plant > const item) = 0;
	virtual void listPlants() const = 0;
	virtual void writeToCSV(const string& fileName, bool append, const char FieldSeparator) const = 0;
	virtual void readFromCSV(const string& fileName, const char FieldSeparator) = 0;
};

