#include "pch.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>

// Default constructor
Utilities::Utilities()
{
}

// Default destructor
Utilities::~Utilities()
{
}

// Returns whether the input string is a string that is used as a quit string
bool Utilities::isNormalQuit(const string& id) {
	return (id == "q" || id == "Q");
}

// Validates a string, requirements are regex match and presence of content and maximum length
bool Utilities::validateRegexString(const string& candidate, const regex& myRegex, const size_t maxlen) {
	return (candidate.length() > 0 && candidate.length() < maxlen && regex_match(candidate, myRegex));
}

// Validates an unsigned integer with maximum six digits and no whitespace
bool Utilities::validateNonNegInt(const string& candidate) {
	const regex intRegex
	("^" + RegexDigit + "{1,6}$");
	return validateRegexString (candidate, intRegex, 6);
}

// Validates an unsigned float with maximum six digits in both integer and fraction parts and no whitespace
bool Utilities::validateNonNegFloat(const string& candidate) {
	const regex floatRegex
	( "^((" + RegexDigit + "{0,6}\\." + RegexDigit + "{1,6})|(" + RegexDigit + "{1,6}(\\." + RegexDigit + "{0,6})?))$" );
	return validateRegexString(candidate, floatRegex, 13);
}

// Inquires cin string until getting a valid one character string with the character in a specific lowercase set, ignoring input case.  Returns the character as lowercase.
// This method can be used only if string::npos always means that the value is not found.
char Utilities::CharSetInput(const string& prompt, const string& inputSet) {
	string inputString;
	char inputChar { ' ' };
	do {
		cout << prompt;
		getline(cin, inputString);
	} while ((inputString.length() != 1)
		|| (inputSet.find(inputChar = tolower(inputString[0])) == string::npos));
	return inputChar;
}

// Returns a string input from command line.  Updates cancellation token if cancel is requested.
// If default values are used and user gives empty string, returns default value.
string Utilities::StringInput(const string& prompt, bool& cancelToken, const bool useDefault, const string& defaultValue) {
	string work { "" };
	cout << prompt + NormalQuitString;
	if (useDefault)
		cout << "Default value " << defaultValue << "  ";
	getline(cin, work);
	if (Utilities::isNormalQuit(work)) {
		cancelToken = true;
	}
	else if (useDefault && work.empty())
		work.assign(defaultValue);
	cout << "\n";
	return work;
}

// Returns a non-negative float input from command line.  Updates cancellation token if cancel is requested.
// If default values are used and user gives empty string, returns default value.
float Utilities::NonNegFloatInput(const string& prompt, bool& cancelToken, const bool useDefault, const float defaultValue) {
	bool inputOK { false };
	string work { "" };
	float retVal { 0 };
	while (!inputOK) {
		cout << prompt + NormalQuitString;
		if (useDefault)
			cout << "Default value " << defaultValue << "  ";
		getline(cin, work);
		if (Utilities::isNormalQuit(work)) {
			cancelToken = true;
			inputOK = true;
		}
		else if (useDefault && work.empty()) {
			inputOK = true;
			retVal = defaultValue;
		}
		else {
			if (Utilities::validateNonNegFloat(work)) {
				retVal = stof(work, nullptr);
				inputOK = true;
			}
		}
		cout << "\n";
	}
	return retVal;
}

// Returns a non-negative integer input from command line.  Updates cancellation token if cancel is requested.
// If default values are used and user gives empty string, returns default value.
int Utilities::NonNegIntInput(const string& prompt, bool& cancelToken, const bool useDefault, const int defaultValue) {
	bool inputOK { false };
	string work { "" };
	int retVal { 0 };
	while (!inputOK) {
		cout << prompt + NormalQuitString;
		if (useDefault)
			cout << "Default value " << defaultValue << "  ";
		getline(cin, work);
		if (Utilities::isNormalQuit(work)) {
			cancelToken = true;
			inputOK = true;
		}
		else if (useDefault && work.empty()) {
			inputOK = true;
			retVal = defaultValue;
		}
		else {
			if (Utilities::validateNonNegInt(work)) {
				retVal = stoi(work, nullptr);
				inputOK = true;
			}
		}
		cout << "\n";
	}
	return retVal;
}

// Asks the file name for an input file.  actionFlag is for cancelling.
string Utilities::TextCommandAcceptInputFileName(char& actionFlag) {

	// Default values if the user does not want to read from file
	string fileName { "" };
	actionFlag = 'q';

	string prompt { "Do you want to read existing plants from a file? Please press y, Y, n, or N, then press ENTER.\n" };
	char action = Utilities::CharSetInput(prompt, "yn");

	if (action == 'y') {

		bool nameNotAccepted { true };
		while (nameNotAccepted) { // Ask file name
			cout << "Please enter a file name where to load plants from, then press ENTER.\n";
			getline(cin, fileName);
			ifstream testFile(fileName);
			if (!(testFile.fail())) {
				nameNotAccepted = false; // File exists, so name is OK, go ahead
				actionFlag = 'o';
			}
			else {
				cout << "File does not exist, what should I do?\n";
				string prompt { "Press n or N to give another file name, q or Q to quit reading\n" };
				prompt.append("Please give a command above and then press ENTER.\n");
				actionFlag = Utilities::CharSetInput(prompt, "nq");
				if (actionFlag == 'q') {
					fileName = ""; // For clarity
					nameNotAccepted = false; // User wants to cancel reading
				}
			}
		}
	}
	return fileName;
}

// Asks the file name for an output file.  actionFlag is for cancelling and deciding whether to append or overwrite if file exists.
string Utilities::TextCommandAcceptOutputFileName(char& actionFlag) {

	// Default values if the user does not want to write to file
	string fileName { "" };
	actionFlag = 'q';

	char action = Utilities::CharSetInput("Do you want to write plants into a file (y, Y, n or N)\n", "yn");

	if (action != 'n') {

		bool nameNotAccepted { true };

		action = ' '; // Ei viitsi jättää y:tä, vaikeuttaisi ylläpitoa
		while (nameNotAccepted) { // Ask file name
			cout << "Please enter a file name where to save plants, then press ENTER.\n";
			getline(cin, fileName);
			ifstream testFile(fileName);
			if (testFile.fail()) {
				nameNotAccepted = false; // File does not exist, so fileName is OK, go ahead
				actionFlag = 'o';
			}
			else {
				cout << "File already exists, what should I do?\n";
				string prompt = "o or O is overwrite (deleting old content), a or A is append, n or N is new file, q or Q is quit\n";
				prompt.append("If appending (keeping all old content), duplicates of already existing ids are appended without deleting the original ones.\n");
				prompt.append("Please give a command above and then press ENTER.\n");
				actionFlag = Utilities::CharSetInput(prompt, "oanq");
				if (actionFlag != 'n') { // Cancel or intentionally overwrite or append to an existing file
					if (actionFlag == 'q') fileName = ""; // Reset fileName for clarity if the user wants to cancel
					nameNotAccepted = false; // Go ahead
				}
			}
		}
	}
	return fileName;
}