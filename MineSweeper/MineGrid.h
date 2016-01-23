/*
Details: MineGrid vars/ functions

*/


class MGrid
{
public:
	MGrid();
	~MGrid();

	
	void setSize(int h, int w, int m);
	int getPos(int colCoord, int rowCoord);


	void initialiseArray();
	void displayGrid();
	void placeMines();
	bool dig(int colCoord, int rowCoord);


private:
	int height, width, numberOfMines;
	int *mArray;
};