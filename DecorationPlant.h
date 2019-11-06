#pragma once
#include "Plant.h"
#include <string>

class DecorationPlant :
	public Plant
{
public:
	DecorationPlant(const int pId, bool& quitRequired);
	DecorationPlant(const int pId, const string& name, const int number, const float costs, const float germinated);
	DecorationPlant(istringstream& iss, char FieldSeparator);
	~DecorationPlant();

	float getAmountGerminated() const;
	shared_ptr<Plant> clone() const;

	bool askPlantFields(const bool useDefault);
	bool askFields(const bool useDefault);
	string getPlantDetails() const;
	string plantToString() const;
	string makeCSVData(const char FieldSeparator) const;
	string makeCSVHeaders(const char FieldSeparator) const;

private:
	float amountGerminated=0;
};

