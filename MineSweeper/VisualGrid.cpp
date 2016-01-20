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
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
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
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
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

void VGrid::displayGrid()
{
	// for each position
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			cout << vArray[(width*r) + c] << ' ';
		}
		cout << endl;
	}
}

int VGrid::flag(int colCoord, int rowCoord)
{
	char currentChar;
	int  isFlagged = 1; // assume position can be flagged 

	// find char at position
	currentChar = vArray[(width * rowCoord) + c];

	// if position can be flagged.
	if (currentChar != 'F')
	{
		vArray[(width * rowCoord) + colCoord] = 'F';
	}
	// if anything is in position. Hopfully will notice if number are in position.
	else
	{
		isFlagged = 0;
	}
	
	return isFlagged;
}


