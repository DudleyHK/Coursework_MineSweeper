/*




*/

#include "ErrorHandling.h"

#include <iostream>
using namespace std;
using namespace ErrorHandling;



/*This function takes the users input as a string allowing the program to 
check the whole input for invalid characters. The function will return an 
error number*/
int ErrorHandling::checkHeightWidth(string &input, int gameMode)
{
	int errorNumber = 0;

	// FOR each char in the string
	for (int i = 0; i < input.length(); i++)
	{
		// IF position is NOT isDigit
		if (!isdigit(input[i]))
		{
			errorNumber = 99;
			break;
		}
	}

	return errorNumber;
}

/*This function checks if the user has entered a valid input at any menu stage.
It checks for one numerical input from the user and will return an error if anything
else is detected. could possibley use this function to check the continueOrQuit
function in the MineSweeper object*/
void ErrorHandling::checkOptionSelect(string &input)
{
	int errorNumber = 0;
	int numberCounter = 0;

	// Check each character in the string
	for (int i = 0; i < input.length(); i++)
	{
		// Get first value in string and check it. This may avoid all other checks


		// IF position is a space
		if (input[i] == ' ')
		{
			continue;
		}

		// if the value in position is numerical +1 to counter
		if (isdigit(input[i]))
		{
			numberCounter++;
		}

		// IF position is NOT isDigit
		if (!isdigit(input[i]))
		{
			errorNumber = 99;
			throw errorNumber;
		}
		else if (numberCounter > 1)
		{
			errorNumber = 98;
			throw errorNumber;
		}
	}
}


/*This function prints out a message depending on the number passed in*/
void ErrorHandling::printMessage(int errorNumber)
{
	switch (errorNumber)
	{
	case 99:
		cout << endl;
		cout << "# Error: invalid input." << endl;
		break;
	case 98:
		cout << endl;
		cout << "# Error: too many selected values." << endl;
		break;
	}// END switch




}






















/*
		switch (gameMode)
		{
		case 1:
			if ((height < 3 || height > 20) || (width < 3 || width > 20))
			{
				cout << "Invalid input." << endl;
			}
			else
			{
				isRepeat = false;
			}

			break;

		case 2:
			if ((height < 5 || height > 20) || (width < 5 || width > 20))
			{
				cout << "Invalid input." << endl;
			}
			else
			{
				isRepeat = false;
			}


			break;

		case 3:
			if ((height < 8 || height > 20) || (width < 8 || width > 20))
			{
				cout << "Invalid input." << endl;
			}
			else
			{
				isRepeat = false;
			}

			break;*/