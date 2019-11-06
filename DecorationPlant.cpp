#include "pch.h"
#include "DecorationPlant.h"
#include "Utilities.h"
#include <iostream>


// Constructor for creating by command line
DecorationPlant::DecorationPlant(const int pId, bool& quitRequired) : Plant(pId, quitRequired) {
	if (!quitRequired) {
		quitRequired = (!askFields(false));
	}
	myType = PLANTTYPE::DECORATION;
}

// Constructor for creating by user interaction
DecorationPlant::DecorationPlant(const int pId, const string& name, const int number, 
	const float costs, const float germinated)
	: Plant(pId, name, number, costs), amountGerminated(germinated)
{
	myType = PLANTTYPE::DECORATION;
}

// Constuctor that constructs an existing decoration plant from stream data
DecorationPlant::DecorationPlant(istringstream& iss, char FieldSeparator)
	: Plant(iss, FieldSeparator)
{
	string f_work;
	getline(iss, f_work, FieldSeparator);
	amountGerminated = stof(f_work, nullptr);
	myType = PLANTTYPE::DECORATION;
}

// Virtual destructor
DecorationPlant::~DecorationPlant()
{
}

// Getter for getting the amount that has germinated
float DecorationPlant::getAmountGerminated() const {
	return amountGerminated;
}

shared_ptr<Plant> DecorationPlant::clone() const {
	return make_shared<DecorationPlant>(DecorationPlant(*this));
}

// Ask plant input fields and update them, return whether cancel had been done
bool DecorationPlant::askPlantFields(const bool useDefault) {
	bool cancelToken = !Plant::askPlantFields(useDefault);
	return (cancelToken) ? false : askFields(useDefault);
}

// Ask input fields of this level and update them, return whether cancel had been done
bool DecorationPlant::askFields(const bool useDefault) {
	bool cancelToken = false;
	amountGerminated = Utilities::NonNegFloatInput("Please give amount germinated ", cancelToken, useDefault, amountGerminated);
	return !cancelToken;
}
// Prints details that may interest the user, except the balance
string DecorationPlant::getPlantDetails() const {
	ostringstream oss;
	oss.clear();
	oss << Plant::getPlantDetails() << " " << " Amount germinated: " << amountGerminated << "\n";
	return oss.str();
}

// Writes the data of a plant to a string
string DecorationPlant::plantToString() const{
	ostringstream oss;
	oss.clear();
	oss << Plant::plantToString() << " Amount germinated: " << amountGerminated;
	return oss.str();
}

// Writes the data of a plant to CSV format
// Commit: must be in the same order as data in makeCSVHeaders
string DecorationPlant::makeCSVData(const char FieldSeparator) const {
	stringstream myStringStream;
	myStringStream.clear();
	myStringStream << Plant::makeCSVData(FieldSeparator) << FieldSeparator << amountGerminated;
	return myStringStream.str();
}

// Writes the header fields for the data of a plant for a CSV file
// Commit: must be in the same order as data in makeCSVData
string DecorationPlant::makeCSVHeaders(const char FieldSeparator) const {
	stringstream myStringStream;
	myStringStream.clear();
	myStringStream << Plant::makeCSVHeaders(FieldSeparator) << FieldSeparator
		<< "AmountGerminated";
	return myStringStream.str();
}

