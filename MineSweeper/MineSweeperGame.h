/*
	Solution: Game Controller Class
	Author: Dudley Dawes
	Summary: Main Class - controlling information management and functionality. This
				Class takes information from the user and passes it to the Mine Grid and 
				Visual Grid. It uses functionality from the Error Handling Namesapce and 
				stores user interface information in the System Namespace.
	

*/

#include "MineGrid.h"
#include "VisualGrid.h"
#include "Settings.h"
#include "System.h"
#include "ErrorHandling.h"

using namespace System;
using namespace ErrorHandling;


class MineSweeper
{
public:
	
	MGrid mineGrid;
	VGrid visualGrid;
	Settings settings;

	Coordinates coordinates;

	/*************************Data Access******************************/

	MineSweeper();
	~MineSweeper();

	void getNumberOfMines();
	void passSize();
	void createNewCoords();

	/****************************PreGame*******************************/

	bool mainMenu();
	char settingsMenu();
	bool loadGame();		

	/*************************Functionality****************************/

	bool playGame();
	void inputGridSize();
	int guessPosition();
	void updateCounter();
	void changeIntToChar();
	void findMinePositions();
	bool continueOrQuit();
	bool menuValidator(int &userInput);		//THIS VALUE NEEDS TO GET CHNAGED 
	
private:

	/*SIZE AND COORDINATE INFORMATION*/
	int height, width, numberOfMines;
	int inputCoordC, inputCoordR;

	/*INPUT VALIDATION*/
	string validateUserInput;
	char errorNumber;
	bool isValid;

	/*MODE AND CONTINUE OPTION*/
	char gameMode;
	bool continueGame;

	/*FLAG INFORMATION*/
	int correctFlags, totalFlags;
};