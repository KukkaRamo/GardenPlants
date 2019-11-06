#pragma once
#include "Plant.h"

class UtilityPlant :
	public Plant
{
public:
	UtilityPlant(const int pId, bool& quitRequired);
	UtilityPlant(const int pId, const string& name, const int number, const float costs, 
		const float amount, const string& unit);
	UtilityPlant(istringstream& iss, char FieldSeparator);
	~UtilityPlant();
	
	float getUtilityAmount() const;
	string getUtilityUnit() const;
	shared_ptr<Plant> clone() const;
	
	bool askPlantFields(const bool useDefault);
	bool askFields(const bool useDefault);
	string getPlantDetails() const;
	string plantToString() const;
	string makeCSVData(const char FieldSeparator) const;
	string makeCSVHeaders(const char FieldSeparator) const;

private:
	float utilityAmount=0;
	string utilityUnit="";
};

