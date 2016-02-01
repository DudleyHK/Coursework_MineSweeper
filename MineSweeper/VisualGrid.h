/*
	Solution: Visual Grid
	Author: Dudley Dawes
	Summary: The visual grid object includes funcitonality involved with interacting
				with and displaying any visual content. This also includes changing
				an integer value and changing it into a char to be displayed after 
				each turn.
*/

class VGrid
{
public:

	/*************************Data Access******************************/

	VGrid();
	~VGrid();

	void reset();

	void setSize(int h, int w, int m);
	char getPos(int colCoord, int rowCoord);
	void setPos(int colCoord, int rowCoord, char currentChar);


	/***************************Run Time*******************************/

	void initialiseArray();	
	void displayGrid();
	bool flag(int colCoord, int rowCoord);
	void changeIntToChar(int colCoord, int rowCoord, int number);


private:
	/* SIZE INFORMATION */
	int height = 0, width = 0, numberOfMines = 0;

	/* VISUAL ARRAY */
	char* vArray = nullptr;
};
