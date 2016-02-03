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
	
	height = 0;
	width = 0;
	numberOfMines = 0;
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

	// SET variable to the value at position
	numberAtPos = mArray[(width * rowCoord) + colCoord];

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

	// UPDATE grid accordingly.
	mineGridCalculations();
}



void MGrid::mineGridCalculations()
{
	// FOR every position in grid
	for (int rowPos = 0; rowPos < height; rowPos++)
	{
		for (int colPos = 0; colPos < width; colPos++)
		{
			// IF the position is a MINE
			if (mArray[(width*rowPos) + colPos] == -1)
			{
				// FOR each of the adjecent squares
				for (int adjacentRow = rowPos - 1; adjacentRow <= rowPos + 1;
					adjacentRow++)
				{
					for (int adjacentCol = colPos - 1; adjacentCol <= colPos + 1;
						adjacentCol++)
					{
						// IF position in bounds
						if (adjacentRow >= 0 && adjacentRow < height)
						{
							if (adjacentCol >= 0 && adjacentCol < width)
							{
								// IF position we're looking at is NOT a mine
								if (mArray[(width*adjacentRow) + adjacentCol] != -1)
								{
									// increment position by one
									mArray[(width*adjacentRow) + adjacentCol]++;
								}
							}
						}
					}
				} // END FOR adjacent positions
			}
		}
	} // END FOR grid positions
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
				counter--; // allow the loop to repeat if a position was NOT found
			}

			counter++;

		} // END WHILE
	}
}