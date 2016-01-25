/*
	Solution: Settings
	Author: Dudley Dawes
	Summary: Settings is only accessed when players wish to change the difficulty
				mode. It is also accessed at the beginning of the game if a mode 
				has not be selected. The functions in places will automatically 
				assign the numberOfMines whether its for a default or standard game.
*/

class Settings
{
public:

	/*************************Data Access******************************/

	Settings();
	
	int getDefaultHeight();
	int getDefaultWidth();
	int getNumberOfMines(int area, int gameMode);

private:
	/* DEFAULT VARIABLES*/
	int defaultHeight, defaultWidth, numberOfMines;
};

