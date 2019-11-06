#include "pch.h"
#include "PlantCollectionWithMap.h"
#include "PlantFactory.h"

// Default constructor
PlantCollectionWithMap::PlantCollectionWithMap()
{
}

// Destructor of the collection
PlantCollectionWithMap::~PlantCollectionWithMap()
{
}

// Checks if a plant with a specific id exists.  Returns the result as boolean.
bool PlantCollectionWithMap::plantExists(const int id) const
{
	return collectionBox.find(id) != collectionBox.end();
}

// Returns a pointer to the plant with a specific id.  An exception follows if the plant does not exist.
shared_ptr<Plant> PlantCollectionWithMap::findPlant(const int id)
{
	return collectionBox.at(id);
}

// Lists fields of all plants in the collection to cout.
void PlantCollectionWithMap::listPlants() const
{
	for (auto& item : collectionBox) {
		cout << item.second->plantToString() + "\n";
	}
}

// Adds a plant to the collection.  Parameter: pointer to the plant to be added.  
// Please check that a plant with the given id does not already exist in the collection before calling this.
void PlantCollectionWithMap::addPlant(shared_ptr<Plant> const plant)
{
	pair<const int, shared_ptr<Plant>> newPair(plant->getId(), plant);
	collectionBox.insert(newPair);
}

// Deletes a plant with a specific id in the collection.  De-allocates the space allocated by new.  
// Nothing happens if the plant does not exist.
void PlantCollectionWithMap::deletePlant(const int id)
{
	collectionBox.erase(id);
}

// Replaces a plant with a specific id in the collection with new input item.  De-allocates the space for old item.
// An exception follows if the plant with the input parameter id as id does not exist.
void PlantCollectionWithMap::updatePlant(const int id, shared_ptr<Plant> const item)
{
	collectionBox[id] = move(item);
}

// If desired, writes the content of the collection to a user specified CSV file.  Overwrites or appends on request.
void PlantCollectionWithMap::writeToCSV(const string& fileName, bool append, const char FieldSeparator) const {

	ofstream myFile;
	if (append) // Append to an existing file
		myFile.open(fileName, ios_base::app);
	else
		myFile.open(fileName); // Creates a file, overwrites if it already exists

	for (auto& item : collectionBox) {
		myFile << (item.second->makeCSVData(FieldSeparator) + "\n");
	}

	myFile.close();
}

// If desired, reads content to the collection from a user specified CSV file.  Writes errors to cout or throws them.
void PlantCollectionWithMap::readFromCSV(const string& fileName, const char FieldSeparator) {

	ifstream myFile;
	myFile.open(fileName);
	string f_work;
	shared_ptr<Plant> plant;
	istringstream iss;
	string inputString;
	while (getline(myFile, inputString)) {
		try {
			iss.clear();
			iss.str(inputString);

			getline(iss, f_work, FieldSeparator);
			if (f_work.length() != 1)
				cerr << "Type is not a one-character string " << f_work << "\n";
			char typeChar = f_work[0];

			plant = PlantFactory::buildPlantFromTypeCharAndStream(iss, FieldSeparator, typeChar);
			if (plant == nullptr) {
				cerr << "Failed to build plant" << f_work << "\n";
			} // Maybe better throw than let the compiler do it?

			if (getline(iss, f_work, FieldSeparator))
				cerr << "Warning: Extra input in input CSV file record.\n";
			pair<const int, shared_ptr<Plant>> newPair(plant->getId(), plant);
			if (plantExists(newPair.first))
				cerr << "Warning: Duplicate id " << newPair.first << ", normal insert done, be sure you know what you do\n";
			collectionBox.insert(newPair);
		}
		catch (exception& e) {
			cerr << "Failed to build a plant from an input line: " << e.what() << "\n";
		}
		iss.clear();
	}
	if (myFile.bad() || !myFile.eof())
		cerr << "Warning: problems in reading the file.\n";
	myFile.close();
}
