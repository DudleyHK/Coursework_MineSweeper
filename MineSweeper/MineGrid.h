/*
	Solution: Mine Grid
	Author: Dudley Dawes
	Summary: This grid stores numerical values used to display the number of mines
				surrounding a position. These calculations are done in the dig function.
				The placeMines function randomly selects positions for the mines which
				are represented by -1.
				
*/
#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std;


class MGrid
{
public:
	/*************************Data Access******************************/

	MGrid();
	~MGrid();

	void reset();
	
	void setSize(int height, int width, int numberOfMines);
	int getPos(int colCoord, int rowCoord);


	/***************************Run Time*******************************/

	void initialiseArray();
	void mineGridCalculations();
	void displayGrid();
	void placeMines();


private:
	/* SIZE INFORMATION */
	int height = 0, width = 0, numberOfMines = 0;

	/* MINE ARRAY */
	int *mArray = nullptr;
};