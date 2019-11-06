#pragma once
#include "Plant.h"
#include "PlantCollection.h"
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

class PlantCollectionWithMap : public PlantCollection
{
public:

	PlantCollectionWithMap();
	~PlantCollectionWithMap();

	bool plantExists(const int id) const;
	shared_ptr<Plant> findPlant(const int id);
	void addPlant(shared_ptr<Plant> const pPlant);
	void deletePlant(const int id);
	void updatePlant(const int id, shared_ptr<Plant> const item);
	void listPlants() const;
	void writeToCSV(const string& fileName, bool append, const char FieldSeparator) const;
	void readFromCSV(const string& fileName, const char FieldSeparator);

private:
	map <const int, shared_ptr<Plant>> collectionBox;
};

