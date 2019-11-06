#include "pch.h"
#include "PlantFactory.h"
#include "PlantTypeInfo.h"
#include "TextCommandController.h"
#include "Utilities.h"
#include <iostream>
#include <stdio.h>

using namespace std;

const string QuitString =
"Do you really want to quit?\ny (or Y) and then ENTER = yes, any other string = no\n";
string commandsAsString;
pair<string, string> insertCommandInstructionPair;

// Constructs a text command controller
TextCommandController::TextCommandController() : CommandController()
{
}

// Destructor for text command controller
TextCommandController::~TextCommandController()
{
	// Delete plants from collection
}

PlantCollection& TextCommandController::getMyPlantCollection() {
	return myPlantCollection;
}

// The Welcome -command when the user starts the program
void TextCommandController::welcome() {
	string startWanted;
	cout << WelcomeString;
	getline(cin, startWanted);
	char actionFlag = 'q';
	string fileName = Utilities::TextCommandAcceptInputFileName(actionFlag);
	if (actionFlag != 'q')
		myPlantCollection.readFromCSV(fileName, FieldSeparator); // For now, a CSV file is the only possible source of input
	// Reading command abbreviations for choosing the command
	stringstream ss;
	ss.clear();
	for (auto item : CommandCollection) {
		ss << item.first;
	}
	commandsAsString = ss.str(); // The string containing the command characters
	// Reading instructions for selecting new plant
	insertCommandInstructionPair = PlantTypeInfo::buildTextInsertGuidingPair();
}

// The Finalize -command when the user has decided to quit the program
void TextCommandController::finalize() {
	char actionFlag = 'q';
	string fileName = Utilities::TextCommandAcceptOutputFileName(actionFlag);
	if (actionFlag != 'q')
		myPlantCollection.writeToCSV(fileName, actionFlag == 'a', FieldSeparator);
	string endAccepted;
	cout << GoodbyeString;
	getline(cin, endAccepted);
}

// Command for inquiring plant id
int TextCommandController::inquireId(bool& flag) {
	string id;
	int iid = 0;
	flag = false;
	do {
		cout << "Please give a small integer ID without white space," + NormalQuitString + "\n";
		cout << "Then press ENTER.\n";
		getline(cin, id);
		if (Utilities::isNormalQuit(id)) {
			flag = true;
			break;
		}
	} while (!Plant::iDCandidateOK(id));
	if (flag == false) {
		iid = stoi(id, nullptr);
	}
	return iid;
}

// Controller to process commands
bool TextCommandController::processCommand() {

	// Wait until getting a real command
	char commandInput = Utilities::CharSetInput(PromptString, commandsAsString);

	return (CommandCollection.at(commandInput).actionMethod) (*this);
}

// Help-command to give commands and instructions to use them
bool TextCommandController::ProcessHelp(TextCommandController& caller) {
	for (auto& i : caller.CommandCollection) {
		const string myText = i.second.getText();
		cout << "Command '" + string(1, i.first)
			+ "' : " + myText + " \n";
	}
	return true;
}

// Command for listing all plants
bool TextCommandController::ProcessList(TextCommandController& caller) {
	caller.getMyPlantCollection().listPlants();
	return true;
}

// Command for creating a plant, plant id is given by user
bool TextCommandController::ProcessCreate(TextCommandController& caller) {
	PlantCollection& collection = caller.getMyPlantCollection();
	bool quitRequired = false;
	int iid = inquireId(quitRequired);
	if (!quitRequired) {
		if (!(collection.plantExists(iid))) {
			char inputChar =
				Utilities::CharSetInput(insertCommandInstructionPair.first, insertCommandInstructionPair.second);
			shared_ptr<Plant> p = PlantFactory::buildPlantFromUser(iid, inputChar);
			if (p != nullptr) {
				collection.addPlant(p);
			}
			else cout << "Creation cancelled.\n";
		}
		else
			cout << "Plant already exists.\n";
	}
	return true;
}

// Command for deleting a plant, id is given by user
bool TextCommandController::ProcessDelete(TextCommandController& caller) {
	PlantCollection& collection = caller.getMyPlantCollection();
	bool quitRequired = false;
	int iid = inquireId(quitRequired);
	if (!quitRequired) {
		if (collection.plantExists(iid)) {
			collection.deletePlant(iid);
		}
		else cout << "No such plant.\n";
	}
	return true;
}

// Command for creating a plant, plant id is given by user
bool TextCommandController::ProcessModify(TextCommandController& caller) {
	PlantCollection& collection = caller.getMyPlantCollection();
	bool quitRequired = false;
	int iid = inquireId(quitRequired);
	if (!quitRequired) {
		if ((collection.plantExists(iid))) {
			shared_ptr<Plant> copyOfOldValues = (collection.findPlant(iid))->clone();
			if (copyOfOldValues == nullptr) {
				cout << "Unknown type, cannot modify " << iid << "\n";
			}
			else {
				quitRequired = !(copyOfOldValues->askPlantFields(true));
				if (!quitRequired) {
					collection.updatePlant(iid, copyOfOldValues);
				}
				else {
					cout << "Modification cancelled.\n";
				}
			}
		}
		else
			cout << "No such plant.\n";
	}
	else cout << "Modification cancelled.\n";
	return true;
}

// Command for printing detail information about a plant, id is given by user
bool TextCommandController::ProcessData(TextCommandController& caller) {
	PlantCollection& collection = caller.getMyPlantCollection();
	bool quitRequired = false;
	int iid = inquireId(quitRequired);
	if (!quitRequired) {
		if (collection.plantExists(iid)) {
			cout << collection.findPlant(iid)->getPlantDetails();
			cout << "\n";
		}
		else cout << "No such plant.\n";
	}
	return true;
}

// Command for accepting the request to quit the program
bool TextCommandController::ProcessQuit(TextCommandController& caller) {
	string inputString;
	cout << QuitString;
	getline(cin, inputString);
	return (inputString != "y") && (inputString != "Y");
}
