/*
	Details: Functions to validate user input

*/

#include "ValidationFunctions.h"

#include <iostream>
using namespace std;


int InputVal::validIn()
{
	int isValid = 1;

	// if console value is not as expected
	if (cin.fail())
	{
		// set value to 0 to say value is bad.
		isValid = 0;
	}

	return isValid;
}

void InputVal::clearCStream()
{
	cin.clear();
	cin.ignore(10000, '\n');
}

