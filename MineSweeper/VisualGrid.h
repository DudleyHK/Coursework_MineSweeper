/*
	Details: Character Grid

*/
#include <iostream>
using namespace std;

class VGrid
{
public:
	VGrid();
	~VGrid();

	void setSize(int h, int w, int m);
	char getPos(int colCoord, int rowCoord);
	void setPos(int colCoord, int rowCoord, char currentChar);

	void initialiseArray();	
	void displayGrid();
	int flag(int colCoord, int rowCoord);


private:
	int height, width, numberOfMines;
	char* vArray;
};
