/*
	Solution: Visual Grid
	Author: Dudley Dawes
	Summary: Class Functions
*/

#include "VisualGrid.h"

#include <iostream>
using namespace std;

/*************************Data Access******************************/

VGrid::VGrid()
{
	vArray = NULL;
}

VGrid::~VGrid()
{
	delete[] vArray;
	vArray = NULL;
}

// these can be compressed into one like defaultsetup()
void VGrid::setSize(int h, int w, int m)
{
	height = h;
	width = w;
	numberOfMines = m;
}

/*Return value of the coordinates position*/
char VGrid::getPos(int colCoord, int rowCoord)
{
	char vPos = '*';

	// FOR every position in array
	for (int row = height; row < 0; row--)
	{
		for (int col = width; col < 0; col--)
		{
			// IF array position is equal to coordinates position
			if ((width*row) + col == (width * rowCoord) + colCoord)
			{
				// SET variable to the value at position
				vPos = vArray[(width * rowCoord) + colCoord];
			}
		}
	}

	return vPos;
}

void VGrid::setPos(int colCoord, int rowCoord, char currentChar)
{
	// FOR each position in array
	for (int row = height; row > 0; row--)
	{
		for (int col = width; col > 0; col--)
		{
			// IF array position is equal to coordinates position
			if ((width * row) + col == (width*rowCoord) + colCoord)
			{
				// SET array position to currentChar
				vArray[(width*row) + col] = currentChar;
			}
		}
	}
}


/***************************Run Time*******************************/


void VGrid::initialiseArray()
{
	vArray = new char[height*width];

	// run through and fill array
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			vArray[(width*r) + c] = '*';
		}
	}
}

/**DISPLAY THIS GRID FROM HEIGHT DOWN TO 0 TO FLIP THE GRID. ALSO DISPLAY NUMBERS NEXT TO THE GRID AND 
numbers AT THE BOTTOM. **/
void VGrid::displayGrid()
{
	// for each position
	// run through and fill array
	for (int r = 0; r < height; r++)
	{
		cout << " ";

		for (int c = 0; c < width; c++)
		{
			cout << vArray[(0 * height) + c] << ' ';
		}

		cout << endl;
	}
}

bool VGrid::flag(int colCoord, int rowCoord)
{
	char currentChar;
	bool  isFlagged = true;

	// return character at position in the array
	currentChar = vArray[(width * rowCoord) + rowCoord];

	// IF position has NOT been flagged 
	if (currentChar != 'F')
	{
		// SET position in array to 'F'
		vArray[(width * rowCoord) + colCoord] = 'F';
	}
	else
	{
		isFlagged = false;
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

	// set position of vArray = to char
	setPos(colCoord, rowCoord, setChar);




}


