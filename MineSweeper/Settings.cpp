/*
		details: Settings functions


*/
#include "Settings.h"

#include <iostream>
using namespace std;


/*************************Data Access******************************/

Settings::Settings()
{
	// Default Settings
	height = 5;
	width = 5;
	numberOfMines = 5;
}

Settings::~Settings()
{
}

/*Although the size is set to default on start up. If the user wishes
to use the default grid size again this function will set it up for them*/
void Settings::setDefaultSize(int h, int w)
{
	height = h;
	width = w;
}

void Settings::setDefaultMines(int m)
{
	numberOfMines = m;
}


int Settings::getHeight()
{
	return height;
}

int Settings::getWidth()
{
	return width;
}

/************************Functionality*****************************/

int Settings::calcMines(int gameMode)
{
	int area = 0;

	area = height*width;

	switch (gameMode)
	{
	case 0:
		setDefaultMines(5);
		break;
	case 1:
		//easy 15%
		numberOfMines = area * 0.15;
		break;
	case 2:
		// medium 25%
		numberOfMines = area * 0.25;
		break;
	case 3:
		// hard 60%
		numberOfMines = area * 0.4;
		break;
	}

	return numberOfMines;
}
