#pragma once
#include <regex>
#include <string>
using namespace std;

static const string RegexDigit { "[[:digit:]]" };
static const string NormalQuitString { " or Q or q to quit " };

class Utilities
{
public:
	Utilities();
	~Utilities();
	static bool isNormalQuit(const string& id);
	static bool validateRegexString(const string& candidate, const regex& myRegex, const size_t maxlen);
	static bool validateNonNegInt(const string& candidate);
	static bool validateNonNegFloat(const string& candidate);
	static char CharSetInput(const string& prompt, const string& inputSet);
	static string StringInput(const string& prompt, bool& cancelToken, const bool useDefault, const string& defaultValue);
	static float NonNegFloatInput(const string& prompt, bool& cancelToken, const bool useDefault, const float defaultValue);
	static int NonNegIntInput (const string& prompt, bool& cancelToken, const bool useDefault, const int defaultValue);
	static string TextCommandAcceptInputFileName(char& actionFlag);
	static string TextCommandAcceptOutputFileName(char& actionFlag);
};

