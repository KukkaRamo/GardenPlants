#pragma once
#include "CommandController.h"
#include "PlantCollectionWithMap.h"
#include "utilities.h"
#include <string>
using namespace std;

class TextCommandController :
	public CommandController
{
public:
	TextCommandController();
	~TextCommandController();

	PlantCollection& getMyPlantCollection();

	void welcome();
	void finalize();
	bool processCommand();

private:
	const char FieldSeparator {','}; // The string between fields in the file where plants are stored
	const string WelcomeString { "Welcome to see my garden.\nPress ENTER to start.\n" };
	const string GoodbyeString { "Welcome back at any time.\nPress ENTER.\n" };
	const string PromptString { "Please give a command.\n  Press h and then ENTER for help.\n" };

	PlantCollectionWithMap myPlantCollection;

	class command {
	public:
		command(const string& ptext,
			bool(*pactionMethod) (TextCommandController&))
			: text(ptext), actionMethod(pactionMethod) {};
		bool(*actionMethod) (TextCommandController&);
		string getText() const { return text; };

	private:
		const string text;
	};

	static int inquireId(bool& flag);

	static bool ProcessHelp(TextCommandController& caller);
	static bool ProcessList(TextCommandController& caller);
	static bool ProcessCreate(TextCommandController& caller);
	static bool ProcessDelete(TextCommandController& caller);
	static bool ProcessData(TextCommandController& caller);
	static bool ProcessModify(TextCommandController& caller);
	static bool ProcessQuit(TextCommandController& caller);

	map <const char, command> CommandCollection  {
		{'h',command("Help", &(TextCommandController::ProcessHelp))},
		{'l',command("List all plants", &(TextCommandController::ProcessList))},
		{'c',command("Create a new plant", &(TextCommandController::ProcessCreate))},
		{'d',command("Delete an existing plant", &(TextCommandController::ProcessDelete))},
		{'i',command("Inquire plant data", &(TextCommandController::ProcessData))},
		{'m',command("Modify plant data", &(TextCommandController::ProcessModify))},
		{'q',command("Quit program", &(TextCommandController::ProcessQuit))}
	};

};

