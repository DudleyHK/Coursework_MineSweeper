/*
	Details: Settings

*/
#include <iostream>
using namespace std;


class Settings
{
public:
	Settings();
	~Settings();

	int getDefaultHeight();
	int getDefaultWidth();
	void setDefaultMines(int m);

	int getNumberOfMines(int area, int gameMode);

private:
	// default setup
	int defaultHeight, defaultWidth, numberOfMines;
};

