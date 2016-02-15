/*
	Solution: Error Handing 
	Author: Dudley Dawes
	Summary: A group of functions designed for different error checking tasks. 
				Each function throws errors which are then printed by the printMessage 
				function. These functions get passed information in their parameters
				to avoid confussion and a clutter of Get and Set functions.
*/
#include <iostream>
using namespace std;


class ErrorHandling
{
public:

	ErrorHandling();
	~ErrorHandling();

	/***************************Run Time*******************************/

	int validateHeightWidth(int height, int width, int gameMode);
	void validateCoordinates(int coordCol, int coordRow, char actionLetter,
		int height, int width);
	void printMessage(int errorNumber);


private:
	int errorNumber = 0;
};