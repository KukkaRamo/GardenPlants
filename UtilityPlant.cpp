#include "pch.h"
#include "Utilities.h"
#include "UtilityPlant.h"
#include <iostream>

// Constructor for creating by command line
UtilityPlant::UtilityPlant(const int pId, bool& quitRequired) : Plant (pId, quitRequired) {
	if (!quitRequired) {
		quitRequired = !(askFields(false));
	}
	myType = PLANTTYPE::UTILITY;
}

// Constructor for creating by user interaction
UtilityPlant::UtilityPlant(const int pId, const string& name, const int number, const float costs, const float amount, const string& unit)
	: Plant(pId, name, number, costs), utilityAmount(amount), utilityUnit(unit)
{
	myType = PLANTTYPE::UTILITY;
}

// Constuctor that constructs an existing utility plant from stream data
UtilityPlant::UtilityPlant(istringstream& iss, char FieldSeparator)
	: Plant(iss, FieldSeparator)
{
	string f_work;
	getline(iss, f_work, FieldSeparator);
	utilityAmount = stof(f_work);
	getline(iss, utilityUnit, FieldSeparator);
	myType = PLANTTYPE::UTILITY;
}

// Virtual destructor
UtilityPlant::~UtilityPlant() {
}

// Getter for utilityAmount
float UtilityPlant::getUtilityAmount() const {
	return utilityAmount;
}

// Getter for utilityUnit
string UtilityPlant::getUtilityUnit() const {
	return utilityUnit;
}

shared_ptr<Plant> UtilityPlant::clone() const {
	return make_shared<UtilityPlant>(UtilityPlant(*this));
}

// Ask plant input fields and update them, return whether cancel had been done
bool UtilityPlant::askPlantFields(const bool useDefault) {
	bool cancelToken = !Plant::askPlantFields(useDefault);
	return (cancelToken) ? false : askFields(useDefault);
}

// Ask input fields for this level and update them, return whether cancel had been done
bool UtilityPlant::askFields(const bool useDefault) {
	bool cancelToken = false;
	utilityAmount=Utilities::NonNegFloatInput("Please give the amount ", cancelToken, useDefault, utilityAmount);
	if (!cancelToken)
		utilityUnit.assign(Utilities::StringInput("\nPlease give the unit ", cancelToken, useDefault, utilityUnit));
	return !cancelToken;
}

// Prints details that may interest the user, except the balance
string UtilityPlant::getPlantDetails() const {
	ostringstream oss;
	oss.clear();
	oss << Plant::getPlantDetails() << " " << " Amount: " << utilityAmount << " Units: " << utilityUnit;
	return oss.str();
}

// Writes the data of a plant to a string
string UtilityPlant::plantToString() const {
	ostringstream oss;
	oss.clear();
	oss << Plant::plantToString() << " Amount: " << utilityAmount << " Units: " << utilityUnit;
	return oss.str();
}

// Writes the data of a plant to CSV format
// Commit: must be in the same order as data in makeCSVHeaders
string UtilityPlant::makeCSVData(const char FieldSeparator) const {
	stringstream myStringStream;
	myStringStream.clear();
	myStringStream << Plant::makeCSVData(FieldSeparator) << FieldSeparator << utilityAmount
		<< FieldSeparator << utilityUnit;
	return myStringStream.str();
}

// Writes the header fields for the data of a plant for a CSV file
// Commit: must be in the same order as data in makeCSVData
string UtilityPlant::makeCSVHeaders(const char FieldSeparator) const {
	stringstream myStringStream;
	myStringStream.clear();
	myStringStream << Plant::makeCSVHeaders(FieldSeparator) << FieldSeparator
		<< "Amount" << FieldSeparator << "Unit";
	return myStringStream.str();
}



