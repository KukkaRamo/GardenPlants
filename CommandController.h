#pragma once
#include "PlantCollection.h"
using namespace std;

class CommandController
{
public:

	CommandController();
	virtual ~CommandController();

	virtual PlantCollection& getMyPlantCollection() = 0;

	virtual void welcome() = 0;
	virtual bool processCommand() = 0;
	virtual void finalize() = 0;
};

