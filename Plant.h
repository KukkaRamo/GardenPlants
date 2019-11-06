#pragma once
#include "PlantTypeEnum.h"
#include <sstream>
#include <string>
using namespace std;

class Plant
{
public:
	
	PLANTTYPE myType = PLANTTYPE::BASIC;
	Plant(const int pId, bool& quitRequired);
	Plant(int id, string name, int number, float costs);
	Plant(istringstream& iss, char FieldSeparator);
	virtual ~Plant();

	int getId() const;
	string getName() const;
	int getNumber() const;
	float getCosts() const;
	virtual shared_ptr<Plant> clone() const;

	static bool iDCandidateOK(const string& candidate);
	virtual bool askPlantFields(const bool useDefault);
	virtual bool askFields(const bool useDefault);
	virtual string getPlantDetails() const;
	virtual string plantToString() const;
	virtual string makeCSVData(const char FieldSeparator) const;
	virtual string makeCSVHeaders(const char FieldSeparator) const;

private:
	int id;
	string name="";
	int number=0;
	float costs=0;
};

