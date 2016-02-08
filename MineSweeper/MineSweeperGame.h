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

class MineSweeper
{
public:


	/*************************Data Access******************************/

	MineSweeper();
	~MineSweeper();
	
	void setNumberOfMines();
	void passSize();
	void createNewCoords();

	/****************************PreGame*******************************/

	bool mainMenu();
	void startGame();
	void displaySettingsMenu();

	void menuValueIsInvaild(int userInput);

	void settingsMenu();
	bool loadGame();		

	/****************************Playing********************************/

	bool playGame();
	void gameLost();
	void resetGame();

	void inputGridSize();
	bool inputGridSizeErrorCheck();
	void inputCoordinates();
	bool inputCoordinatesErrorCheck();

	void actOnLetterInput();
	int actOnLetterInputDig();

	void updateCounter();
	bool checkIfPlayerWon();
	void locateAllMines();

	bool continueOrQuit();

private:
	MGrid *mineGrid = new MGrid;
	VGrid *visualGrid = new VGrid;
	Display *display = new Display;
	Settings settings;
	ErrorHandling errorHandling;


	/* SIZE AND COORDINATE INFORMATION */
	int height = 0, width = 0, numberOfMines = 0;
	int inputCoordC = 0, inputCoordR = 0;
	char actionLetter = 0;

	/* COORDINATES USED BUT THE PROGRAM (USER INPUT - 1) */
	int systemRowCoord = 0;
	int systemColCoord = 0;

	/* INPUT VALIDATION */
	int errorNumber = 0;
	int returnCode = 0;

	/* MODE AND CONTINUE OPTION */
	int gameMode = 0;
	bool continueGame = false;

	/* FLAG INFORMATION */
	int correctFlags = 0, totalFlags = 0;
};