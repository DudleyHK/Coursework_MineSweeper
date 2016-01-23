/*
	Details: Visual Grid Functionality


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


/************************Functionality*****************************/


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
	bool  isFlagged = true; // assume position can be flagged 

	// find char at position
	currentChar = vArray[(width * rowCoord) + rowCoord];

	// if position can be flagged.
	if (currentChar != 'F')
	{
		vArray[(width * rowCoord) + colCoord] = 'F';
	}
	// if anything is in position. Hopfully will notice if number are in position.
	else
	{
		isFlagged = false;
	}
	
	return isFlagged;
}


