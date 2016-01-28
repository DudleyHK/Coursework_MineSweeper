/*
	Solution: Error Handling 
	Author: Dudley Dawes
	Summary: Class Functions
*/
#include "ErrorHandling.h"

#include <iostream>
using namespace std;


/***************************Run Time*******************************/


/*This function takes the users grid size input aand check it against the 
game mode settings. It will throw an exception if an error is found*/
int ErrorHandling::validateHeightWidth(int height, int width, int gameMode)
{
	errorNumber = 0;

	// depending on the game mode 
	if (gameMode == 1)
	{
		if ((height < 4 || height > 20) || (width < 4 || width > 20))
		{
			errorNumber = 8;
		}
	}
	else if (gameMode == 2)
	{
		if ((height < 5 || height > 20) || (width < 5 || width > 20))
		{
			errorNumber = 8;
		}
	}
	else if (gameMode == 3)
	{
		if ((height < 8 || height > 20) || (width < 8 || width > 20))
		{
			errorNumber = 8;
		}
	}

	return errorNumber;
}

/*Function to deal with the user input coordinate guess and if action letter character
is valid */
void ErrorHandling::validateCoordinates(int coordCol, int coordRow, char actionLetter,
	int height, int width)
{
	
	// Check coordinates 
	if (coordCol < 0 || coordCol > width - 1)
	{
		errorNumber = 7;
		throw errorNumber;
	}

	if (coordRow < 0 || coordRow > height - 1)
	{
		errorNumber = 7;
		throw errorNumber;
	}

	// check action letter
	if (actionLetter != 'F')
	{
		if (actionLetter != 'D')
		{
			if (actionLetter != 'Q')
			{
				errorNumber = 6;
				throw errorNumber;
			}
		}
	}
}

/*This function prints out a message depending on the number passed in*/
void ErrorHandling::printMessage(int n)
{
	errorNumber = n;

	switch (errorNumber)
	{
	case 9:
		cout << endl;
		cout << "# Error: invalid input." << endl;
		break;
	case 8:
		cout << endl;
		cout << "# Error: values don't match game type." << endl;
		break;
	case 7:
		cout << endl;
		cout << "# Error: coordinates invalid." << endl;
		break;
	case 6:
		cout << endl;
		cout << "# Error: character invalid" << endl;
		break;
	}// END switch
}