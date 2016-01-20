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