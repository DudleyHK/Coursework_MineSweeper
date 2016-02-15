/*
	Solution: Visual Grid
	Author: Dudley Dawes
	Summary: Class Functions
*/

#include "VisualGrid.h"


/*************************Data Access******************************/

VGrid::VGrid()
	: vArray(nullptr),
	height(0),
	width(0),
	numberOfMines(0)
{
	//constructer

}


VGrid::~VGrid()
{
	reset();
}


void VGrid::reset()
{
	delete[] vArray;
	vArray = nullptr;

	height = 0;
	width = 0;
	numberOfMines = 0;
}


void VGrid::setSize(int h, int w, int m)
{
	height = h;
	width = w;
	numberOfMines = m;
}


/*Return value of the coordinates position*/
char VGrid::getPos(int colCoord, int rowCoord)
{
	char characterAtPos = '*';

	characterAtPos = vArray[(width * rowCoord) + colCoord];

	return characterAtPos;
}


/* SET array position to currentChar */
void VGrid::setPos(int colCoord, int rowCoord, char currentChar)
{
	vArray[(width*rowCoord) + colCoord] = currentChar;
}


/***************************Run Time*******************************/


/*Fill the array with the standard character*/
void VGrid::initialiseArray()
{
	// create NEW array
	vArray = new char[height*width];

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			vArray[(width*r) + c] = '*';
		}
	}
}


void VGrid::displayGrid()
{
	int rowNo = 0;

	// FOR every row
	for (int r = 0; r < height; r++)
	{
		rowNo++;

		if (rowNo < 10)
		{
			// move two away from side
			cout << "  " << rowNo << "| ";
		}
		else
		{
			// move one spce from side
			cout << " " << rowNo << "| ";
		}

		// FOR every column
		for (int c = 0; c < width; c++)
		{

			cout << vArray[(width*r) + c] << ' ';
		}

		cout << endl;
	}
}


bool VGrid::flag(int colCoord, int rowCoord)
{
	char currentChar;
	bool  isFlagged = true;

	// return character at position in the array
	currentChar = vArray[(width * rowCoord) + colCoord];

	// if the position is already flagged
	if (currentChar == 'F')
	{
		// unflag
		vArray[(width * rowCoord) + colCoord] = '*';
	}
	// if its anything other than astrix
	else if (currentChar != '*')
	{
		// return code
		isFlagged = false;
	}
	// IF position has NOT been flagged 
	else
	{
		// SET position in array to 'F'
		vArray[(width * rowCoord) + colCoord] = 'F';
	}

	
	return isFlagged;
}


void VGrid::changeIntToChar(int colCoord, int rowCoord, int number)
{
	char setChar = '*';

	switch (number)
	{
	case -1:
		setChar = '!';
		break;
	case 0:
		setChar = '0';
		break;
	case 1:
		setChar = '1';
		break;
	case 2:
		setChar = '2';
		break;
	case 3:
		setChar = '3';
		break;
	case 4:
		setChar = '4';
		break;
	case 5:
		setChar = '5';
		break;
	case 6:
		setChar = '6';
		break;
	case 7:
		setChar = '7';
		break;
	case 8:
		setChar = '8';
		break;
	}

	setPos(colCoord, rowCoord, setChar);
}


