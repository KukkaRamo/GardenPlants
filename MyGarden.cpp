// MyGarden.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "TextCommandController.h"
#include <exception>
#include <iostream>

int main()
{
	try {
		TextCommandController myController;

		// Just a stupid sequential flow, no events here
		myController.welcome();
		while (myController.processCommand());
		myController.finalize();
	}
	catch (exception& e) {
		cerr << "I am sick.  Pelase contact my author to cure me.\n";
		cerr << "The symptoms are: ";
		cerr << e.what();
	}
}
