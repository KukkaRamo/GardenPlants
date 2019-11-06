#include "pch.h"
#include "Plant.h"
#include "PlantFactory.h"
#include "Utilities.h"

// Constructor for creating by command line
Plant::Plant(const int pId, bool& quitRequired) {
	id = pId;
	quitRequired = !(askFields(false));
}

// Constructor for creating by user interaction
Plant::Plant(int pId, string name, int number, float costs) : id(pId), name(name), number(number), costs(costs)
{
}

// Constuctor that constructs an existing plant from stream data
Plant::Plant(istringstream& iss, char FieldSeparator)
{
	string field_work;
	getline(iss, field_work, FieldSeparator);
	id = stoi(field_work);
	getline(iss, name, FieldSeparator);
	getline(iss, field_work, FieldSeparator);
	number = stoi(field_work);
	getline(iss, field_work, FieldSeparator);
	costs = stof(field_work);
}

// Virtual destructor
Plant::~Plant()
{
}

// A getter for id
int Plant::getId() const {
	return id;
}

// A getter for name
string Plant::getName() const {
	return name;
}

// A getter for number
int Plant::getNumber() const {
	return number;
}

// A getter for costs
float Plant::getCosts() const {
	return costs;
}

shared_ptr<Plant> Plant::clone() const {
	return make_shared<Plant> (Plant(*this));
}

// Ask plant input fields and update them, return whether cancel had been done
bool Plant::askPlantFields(const bool useDefault) {
	return Plant::askFields(useDefault);
}

// Ask plant base class input fields and update them, return whether cancel had been done
bool Plant::askFields(const bool useDefault) {
	bool cancelToken = false;
	name.assign(Utilities::StringInput("\nPlease give the name ", cancelToken, useDefault, name));
	if (!cancelToken) {
		number = Utilities::NonNegIntInput("Please give the number ", cancelToken, useDefault, number);
		if (!cancelToken)
			costs = Utilities::NonNegFloatInput("Please give the costs ", cancelToken, useDefault, costs);
	}
	return !cancelToken;
}

// Returns whether the input string is a valid id
bool Plant::iDCandidateOK(const string& candidate) {
	const size_t maxlen = 7; // Ei tarvita liian pitkiä idtä eli ylivuotoriskiä, kun ei tällä ohjelmalla kuitenkaan jakseta antaa montaa tiliä
	const regex IDRegex("(-|\\+)?" + RegexDigit + "+");
	return Utilities::validateRegexString(candidate, IDRegex, maxlen);
}

// Prints details of the plant, id first
string Plant::getPlantDetails() const {
	ostringstream oss;
	oss.clear();
	oss << "Id: " << getId() << " Type: " << PlantTypeInfo::plantTypeToUserChar(myType)
		<< " Name: " << getName() << " Number: " << getNumber() << " Costs: " << getCosts();
	return oss.str();
}

// Writes the basic data of a plant to a string
string Plant::plantToString() const {
	ostringstream oss;
	oss.clear();
	oss << " Type: " << PlantTypeInfo::plantTypeToUserChar(myType) << " Id: " << getId()
		<< " Name: " << getName() << " Number: " << getNumber() << " Costs: " << getCosts();
	return oss.str();
}

// Writes the basic data of a plant to CSV format.
// Commit: type as user character
// Commit: must be in the same order as data in makeCSVHeaders
string Plant::makeCSVData(const char FieldSeparator) const {
	ostringstream oss;
	oss.clear();
	oss << PlantTypeInfo::plantTypeToUserChar(myType) << FieldSeparator << getId() << FieldSeparator
		<< getName() << FieldSeparator << getNumber() << FieldSeparator << getCosts(); ;
	return oss.str();
}

// Writes the header fields for the basic data of a plant for a CSV file
// Commit: must be in the same order as data in makeCSVData
string Plant::makeCSVHeaders(const char FieldSeparator) const {
	ostringstream oss;
	oss.clear();
	oss << "Type" << FieldSeparator << "Id" << FieldSeparator << "Name" << FieldSeparator
		<< "Number" << FieldSeparator << "Costs";
	return oss.str();
}
