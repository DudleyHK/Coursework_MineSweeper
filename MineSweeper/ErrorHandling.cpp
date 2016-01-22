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