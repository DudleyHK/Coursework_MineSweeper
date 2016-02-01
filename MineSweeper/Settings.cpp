/*
	Solution: Settings
	Author: Dudley Dawes
	Summary: Class Functions
*/

#include "Settings.h"

#include <iostream>
using namespace std;


/*************************Data Access******************************/

Settings::Settings()
	:defaultHeight(10),
	defaultWidth(10),
	numberOfMines(10)
{
	// constructer
}

Settings::~Settings()
{
	//empty
}

/*Functions managing the default settings*/
int Settings::getDefaultHeight()
{
	return defaultHeight;
}

int Settings::getDefaultWidth()
{
	return defaultWidth;
}

/***************************Run Time*******************************/

int Settings::getNumberOfMines(int area, int gameMode)
{
	// answers convertted from variable type double to integers
	switch (gameMode)
	{
	case 0:
		numberOfMines = 10;
		break;
	case 1:
		//easy 15%
		numberOfMines = (int)(area * 0.15);
		break;
	case 2:
		// medium 20%
		numberOfMines = (int)(area * 0.2);
		break;
	case 3:
		// hard 30%
		numberOfMines = (int)(area * 0.3);
		break;
	}

	return numberOfMines;
}