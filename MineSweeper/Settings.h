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

	int getHeight();
	int getWidth();
	int getNumMines();
	void setDefaultSize(int h, int w);
	void setDefaultMines(int m);

	int calcMines(char gameMode);

private:
	// default setup
	int height, width, numberOfMines;
};

