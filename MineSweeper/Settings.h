/*
	Solution: Settings
	Author: Dudley Dawes
	Summary: Settings is only accessed when players wish to change the difficulty
				mode. It is also accessed at the beginning of the game if a mode 
				has not be selected. The functions in places will automatically 
				assign the numberOfMines whether its for a default or standard game.
*/

#include <iostream>
using namespace std;

class Settings
{
public:

	/*************************Data Access******************************/

	Settings();
	~Settings();

	int getDefaultHeight();
	int getDefaultWidth();
	int getNumberOfMines(int area, int gameMode);

private:
	/* DEFAULT VARIABLES*/
	int defaultHeight = 0, defaultWidth = 0, numberOfMines = 0;
};

