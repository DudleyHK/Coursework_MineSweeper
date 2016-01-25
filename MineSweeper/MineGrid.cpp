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
{
	mArray = NULL;
}

MGrid::~MGrid()
{
	delete[] mArray;
	mArray = NULL;
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
	int pos = 0;

	// FOR every position in grid
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			// IF coordintes match position in loop
			if ((width*row) + col == (width * rowCoord) + colCoord)
			{
				// SET variable to the value at position
				pos = mArray[(width * rowCoord) + colCoord];
			}
		}
	}

	return pos;
}



/***************************Run Time*******************************/

void MGrid::initialiseArray()
{
	// create new array
	mArray = new int[height*width];

	// FOR each position
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			// initialise with 0
			mArray[(width*r) + c] = 0;
		}
	}
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
	srand(time(NULL));

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

bool MGrid::dig(int colCoord, int rowCoord)
{
	bool isSafe = true;
	int currVal = 0, counter = 0;


	// GET value at coordinates position
	currVal = mArray[(width*rowCoord) + colCoord];

	// IF value at position is NOT a MINE 
	if (currVal != -1)
	{
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
	else
	{
		// IF player has hit a bomb
		isSafe = false;
	}

	return  isSafe; 
}