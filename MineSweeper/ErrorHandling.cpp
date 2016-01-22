/*e




*/

#include "ErrorHandling.h"

#include <iostream>
#include <string>
using namespace std;
using namespace ErrorHandling;



/*This function takes the users input as a string allowing the program to 
check the whole input for invalid characters. The function will return an 
error number*/
void ErrorHandling::validateHeightWidth(int height, int width, char gameMode)
{
	int errorNumber = 0;

	// depending on the game mode 
	if (gameMode == 1)
	{
		if ((height < 3 || height > 20) || (width < 3 || width > 20))
		{
			errorNumber = 8;
			throw errorNumber;
		}
	}
	else if (gameMode == 2)
	{
		if ((height < 5 || height > 20) || (width < 5 || width > 20))
		{
			errorNumber = 8;
			throw errorNumber;
		}
	}
	else if (gameMode == 3)
	{
		if ((height < 8 || height > 20) || (width < 8 || width > 20))
		{
			errorNumber = 8;
			throw errorNumber;
		}
	}
}

/*This function checks if the user has entered a valid input at any menu stage.
It checks for one numerical input from the user and will throw an error if anything
else is detected bar blank spaces. */
void ErrorHandling::validateMenuSelection(char *input)
{
	int errorNumber = 0;
	int numberCounter = 0;

	// Check each element in string
	for (int i = 0; i < strlen(input); i++)
	{
		// IF element is NOT a digit.
		if (!isdigit(input[i]))
		{
			// IF element is a BLANK SPACE
			if (input[i] == ' ')
			{
				// RUN next iteration
				continue;
			}
			else
			{
				// ERROR
				errorNumber = 9;
				throw errorNumber;
			}
		}

		// IF element is numerical
		if (isdigit(input[i]))
		{
			numberCounter++;
		}

		// IF string has more than one number
		if (numberCounter > 1)
		{
			// ERROR
			errorNumber = 9;
			throw errorNumber;
		}
	}
}


/*This function prints out a message depending on the number passed in*/
void ErrorHandling::printMessage(char errorNumber)
{
	switch (errorNumber)
	{
	case '9':
		cout << endl;
		cout << "# Error: invalid input." << endl;
		break;
	case '8':
		cout << endl;
		cout << "# Error: values don't match game type." << endl;
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