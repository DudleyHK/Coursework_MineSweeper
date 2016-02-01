/*
	Solution: Mine Grid
	Author: Dudley Dawes
	Summary: Class Functions
*/
#include "MineGrid.h"


#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std;


/*************************Data Access******************************/

MGrid::MGrid()
	: mArray(nullptr),
	height(0),
	width(0),
	numberOfMines(0)
{
	// constructor
}

MGrid::~MGrid()
{
	reset();
}

void MGrid::reset()
{
	// delte of the heap and set to no memory
	delete[] mArray;
	mArray = nullptr;
}

void MGrid::setSize(int h, int w, int m)
{
	height = h;
	width = w;
	numberOfMines = m;
}

/*Returns value at passed in coordinates position*/
int MGrid::getPos(int colCoord, int rowCoord)
{
	int numberAtPos = 0;

	// FOR every position in grid
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			// IF coordintes match position in loop
			if ((width*r) + c == (width * rowCoord) + colCoord)
			{
				// SET variable to the value at position
				numberAtPos = mArray[(width * rowCoord) + colCoord];
			}
		}
	}

	return numberAtPos;
}

/***************************Run Time*******************************/

/*Fill the array with the standard number*/
void MGrid::initialiseArray()
{
	// Create NEW array
	mArray = new int[height*width];

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			mArray[(width*r) + c] = 0;
		}
	}

	// randomly set mine positions
	placeMines();
}

void MGrid::displayGrid()
{
	// FOR every position
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			// output value at position
			cout << mArray[(width*r) + c] << ' ';
		}

		cout << endl;
	}
}

void MGrid::placeMines()
{
	// Random function
	srand((unsigned int)(time(0)));

	int pos = 0, counter = 0;

	for (int i = 0; i < numberOfMines; i++)
	{
		counter = 0;

		while (counter < 1)
		{
			// SET random number between 0 and total area
			pos = rand() % (height*width);

			// IF the position free
			if (mArray[pos] == 0)
			{
				// SET position as MINE
				mArray[pos] = -1;
			}
			else
			{
				// minus counter to go around the loop again.
				counter--;
			}

			// once MINE is place increment counter
			counter++;

		} // END WHILE
	}
}

void MGrid::dig(int colCoord, int rowCoord)
{
	bool isSafe = true;
	int counter = 0;


	// FOR 8 adjenscent positions
	for (int row = rowCoord - 1; row <= rowCoord + 1; row++)
	{
		for (int col = colCoord - 1; col <= colCoord + 1; col++)
		{
			// IF position in bounds
			if (row >= 0 && row < height)
			{
				if (col >= 0 && col < width)
				{
					// IF position is a mine
					if (mArray[(width*row) + col] == -1)
					{
						// increment counter by one
						counter++;
					}
				}
			}
		}
	} // END for loop


	// SET value at position to value of counter
	mArray[(width*rowCoord) + colCoord] = counter;
}