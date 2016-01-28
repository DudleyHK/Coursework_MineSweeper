/*
	Solution: Game Controller
	Author: Dudley Dawes
	Summary: Main Class - controlling information management and functionality. This
				Class takes information from the user and passes it to the Mine Grid 
				and Visual Grid. It uses functionality from the Error Handling class 
				and stores and prints user interface information from the System namespace.
*/

#include "MineGrid.h"
#include "VisualGrid.h"
#include "Settings.h"
#include "Display.h"
#include "ErrorHandling.h"

using namespace Display;

class MineSweeper
{
public:
	
	MGrid *mineGrid = new MGrid;
	VGrid visualGrid;
	Settings settings;
	ErrorHandling errorHandling;

	/*************************Data Access******************************/

	MineSweeper();
	
	void getNumberOfMines();
	void passSize();
	void createNewCoords();

	/****************************PreGame*******************************/

	bool mainMenu();
	void settingsMenu();
	bool loadGame();		

	/***************************Run Time*******************************/

	bool playGame();
	void inputGridSize();
	void inputCoordinates();
	void actOnCoordInput();
	void locateAllMines();
	void updateCounter();
	bool continueOrQuit();


private:

	/* SIZE AND COORDINATE INFORMATION */
	int height, width, numberOfMines;
	int inputCoordC, inputCoordR;
	char actionLetter;

	/* COORDINATES USED BUT THE PROGRAM (USER INPUT - 1) */
	int systemRowCoord;
	int systemColCoord;

	/* INPUT VALIDATION */
	int errorNumber;
	int returnCode;

	/* MODE AND CONTINUE OPTION */
	int gameMode;
	bool continueGame;

	/* FLAG INFORMATION */
	int correctFlags, totalFlags;
};