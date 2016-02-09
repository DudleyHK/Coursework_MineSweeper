/*
	Solution: Mine Sweeper Game	
	Author: Dudley Dawes
	Summary: Class Functions and compliers start point main(). All system calls are windows
				specifc ie system ("cls").
*/

#include "MineSweeperGame.h"

#include <iostream>
using namespace std;


/**START**/
int main()
{
	MineSweeper *msGame = new MineSweeper;
	Display display;

	bool gameLoop = false;


	gameLoop = true;
	while (gameLoop)
	{
		display.welcome();
		gameLoop = msGame->mainMenu();

	} // END loop


	delete msGame;
	msGame = nullptr;

	return 0;
}


/**************************Data Access******************************/

MineSweeper::MineSweeper()
	: gameMode(-1),
	continueGame(true)
{
	// constuctor
}


MineSweeper::~MineSweeper()
{
	// empty
}


/* return default values if game mode is 0. Else calculate number of mines 
based on the difficult mode.*/
void MineSweeper::setNumberOfMines()
{
	int area = height * width;

	numberOfMines = settings.getNumberOfMines(area, gameMode);
}


/*Pass Height, Width and Number of Mines to the Mine Grid and Visual Grid*/
void MineSweeper::passSize()
{
	mineGrid->setSize(height, width, numberOfMines);
	visualGrid->setSize(height, width, numberOfMines);
}


/*Create new coordinate variables to be used by the program.*/
void MineSweeper::createNewCoords()
{
	systemRowCoord = inputCoordR - 1;
	systemColCoord = inputCoordC - 1;
}


/****************************PreGame********************************/

bool MineSweeper::mainMenu()
{
	bool isRepeat = false;
	int userInput = 0;


	display->mainMenuInterface();


	// RUN loop until input is valid
	isRepeat = true;
	while (isRepeat)
	{
		cout << "Selection: ";

		cin >> userInput;
	

		switch (userInput)
		{
		case 1:
			startGame();
			break;

		case 2:
			displaySettingsMenu();
			break;

		case 3:
			// break loop and quit program
			isRepeat = false;
			continueGame = false;

			// delete objects memeory
			delete display;
			display = nullptr;

			delete mineGrid;
			mineGrid = nullptr;

			delete visualGrid;
			visualGrid = nullptr;

			break;

		default:
			menuValueIsInvaild(userInput);

			break;

		} // END userInput switch
	} // END menu loop

	
	return continueGame;
}


void MineSweeper::startGame()
{
	// IF game mode has NOT been selected
	if (gameMode == -1)
	{
		// SET default mode
		gameMode = 0;

		height = settings.getDefaultHeight();
		width = settings.getDefaultWidth();
	}

	setNumberOfMines();

	// clear console
	system("cls");

	display->welcome();

	continueGame = loadGame();
}


void MineSweeper::displaySettingsMenu()
{
	// clear console
	system("cls");

	display->welcome();

	settingsMenu();

	display->mainMenuInterface();
}

/*if the number entered in the menu option is incorrect*/
void MineSweeper::menuValueIsInvaild(int userInput)
{
	cout << endl;
	cout << "Menu value " << userInput << " does not exist" << endl;

	display->tryAgain();
}


void MineSweeper::settingsMenu()
{
	bool isRepeat = false;
	int userInput = 0;


	display->settingsInterface();
	
	isRepeat = true;
	while (isRepeat)
	{
		cout << "Selection: ";

		cin >> userInput;


		// SET game mode related to the players choice and break WHILE loop to continue.
		switch (userInput)
		{
		case 0:
			gameMode = 0;
			isRepeat = false;
			break;

		case 1:
			gameMode = 1;
			isRepeat = false;
			break;

		case 2:
			gameMode = 2;
			isRepeat = false;
			break;

		case 3:
			gameMode = 3;
			isRepeat = false;
			break;

		default:
			menuValueIsInvaild(userInput);
			break;

		}// END switch
	}// END menu loop


	// IF game mode is NOT default
	if (gameMode != 0)
	{
		inputGridSize();
	}
	else
	{
		height = settings.getDefaultHeight();
		width = settings.getDefaultWidth();		
	}

	setNumberOfMines();
	
	// clear the console
	system("cls");

	display->welcome();
}


/*This function sets and initialise the objects/ variables needed to run the game.*/
bool MineSweeper::loadGame()
{
	passSize();
	
	mineGrid->initialiseArray();
	visualGrid->initialiseArray();


	continueGame = playGame();

	return continueGame;
}

/****************************Playing********************************/

bool MineSweeper::playGame()
{
	bool inGame = false;

	// SET unused value
	returnCode = 5;


	display->instructions();

	// print how many mines are hidden message
	cout << numberOfMines << " mines are hidden." << endl;


	inGame = true;
	while (inGame)
	{
		cout << endl;
		cout << "===============================================" << endl << endl;

		visualGrid->displayGrid();

		inputCoordinates();

		switch (returnCode)
		{
		case -1:
			gameLost();
			continueGame = continueOrQuit();

			inGame = false;
			break;

		case 0: 
			cout << "option unavailable. please check and try again" << endl;
			break;

		case 1: 
			resetGame();
			inGame = false;
		}


		if (returnCode != -1 && returnCode != 1)
		{
			inGame = checkIfPlayerWon();
		}

	} // END while


	return continueGame;
}


void MineSweeper::gameLost()
{
	// WHILE the number of mines displayed is less than total number of mines
	for (int numOfMinesDisplayed = 0; numOfMinesDisplayed <= numberOfMines; 
		numOfMinesDisplayed++)
	{
		locateAllMines();
	}

	visualGrid->displayGrid();

	display->looser();
}


/*Delete array memory and output displays*/
void MineSweeper::resetGame()
{
	// clear the console
	system("cls");

	display->welcome();

	display->mainMenuInterface();

	mineGrid->reset();
	visualGrid->reset();
}


void MineSweeper::inputGridSize()
{
	bool isRepeat = false, isValid = false;

	cout << endl;
	cout << "---------------------------------------" << endl;
	cout << "Enter grid size" << endl;


	isRepeat = true;
	while (isRepeat)
	{
		// READ inputs
		cout << "Height: ";
		cin >> height;

		cout << "Width: ";
		cin >> width;

		isValid = inputGridSizeErrorCheck();		

		// IF isValid is TRUE exit loop
		if (isValid == true)
		{
			isRepeat = false;
		}

	}// END while
}


/* Function to validate inputted height and width. */
bool MineSweeper::inputGridSizeErrorCheck()
{
	bool isValid = false;

	try
	{
		errorNumber = errorHandling.validateHeightWidth(height, width, gameMode);

		if (errorNumber == 0)
		{
			isValid = true;
		}
		else
		{
			throw errorNumber;
		}
	}
	catch (int n)
	{
		errorHandling.printMessage(n);

		isValid = false;

		display->tryAgain();
	}

	return isValid;
}


void MineSweeper::inputCoordinates()
{
	bool isValid = false;


	cout << endl << endl;

	while (!isValid)
	{
		cout << "Coordinates: ";

		// READ input
		cin >> inputCoordC;
		cin >> inputCoordR;


		createNewCoords();


		cout << "Action: ";

		// READ input
		cin >> actionLetter;

		cout << endl;

		// if input is lower case, make upper case.
		if (islower(actionLetter))
		{
			actionLetter = toupper(actionLetter);
		}


		isValid = inputCoordinatesErrorCheck();

	} // END while


	actOnLetterInput();
}


/* Function to validate inputted coordinates and action. */
bool MineSweeper::inputCoordinatesErrorCheck()
{
	bool isValid = false;


	try
	{
		errorHandling.validateCoordinates(systemColCoord, systemRowCoord,
			actionLetter, height, width);

		isValid = true;
	}
	catch (int n)
	{
		isValid = false;

		errorHandling.printMessage(n);

		display->tryAgain();
	}

	return isValid;
}


void MineSweeper::actOnLetterInput()
{
	bool isFlagged = false;


	switch (actionLetter)
	{
	case 'F':

		isFlagged = visualGrid->flag(systemColCoord, systemRowCoord);

		if (isFlagged == false)
		{
			// option unavailable
			returnCode = 0;
		}
		break;

	case 'D':
		returnCode = actOnLetterInputDig();
		break;

	case 'Q': // to exit the game
		returnCode = 1;
		break;
	}
}


int MineSweeper::actOnLetterInputDig()
{
	int valueAtPos = 0;
	char characterAtPos = '*';

	valueAtPos = mineGrid->getPos(systemColCoord, systemRowCoord);
	characterAtPos = visualGrid->getPos(systemColCoord, systemRowCoord);

	// if position is a mine
	if (valueAtPos == -1)
	{
		returnCode = -1;
	}
	else
	{
		if (characterAtPos != 'F')
		{
			visualGrid->changeIntToChar(systemColCoord, systemRowCoord, valueAtPos);
		}
	}

	return returnCode;
}


bool MineSweeper::checkIfPlayerWon()
{
	bool inGame = true;


	// update number of correctly flagged mines
	updateCounter();

	if (correctFlags == numberOfMines && totalFlags == numberOfMines)
	{
		// Print a line.
		cout << endl;
		cout << "===============================================" << endl << endl;

		// output the visual grid.
		visualGrid->displayGrid();
		display->winner();

		continueGame = continueOrQuit();

		inGame = false;
	}

	return inGame;
}


/*Check each element of the grids to check the number of total flags on the map, 
and the number of flags correctly positioned on the map.*/
void MineSweeper::updateCounter()
{
	int totalFlagsCounter = 0, correctFlagsCounter = 0;

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			char vPos = visualGrid->getPos(col, row);
			int mPos = mineGrid->getPos(col, row);

			if (vPos == 'F')
			{
				totalFlagsCounter++;

				// IF flag is placed on a MINE
				if (mPos == -1)
				{
					correctFlagsCounter++;
				}
			}
		}
	}

	// SET global variables
	totalFlags = totalFlagsCounter;
	correctFlags = correctFlagsCounter;
}


/*This functions runs through the Mine array and locating each mine, and calling 
a function to set the relative position in the Visual array as a mine*/
void MineSweeper::locateAllMines()
{
	int valueAtPos = 0;

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			valueAtPos = mineGrid->getPos(c, r);

			if (valueAtPos == -1)
			{
				visualGrid->changeIntToChar(c, r, valueAtPos);
			}
		}
	}
}


bool MineSweeper::continueOrQuit()
{
	char userInput = 'Y';
	bool isRepeat = false;


	isRepeat = true;
	while (isRepeat)
	{
		cout << endl;
		cout << "Continue Y/N?" << endl;
		cin >> userInput;

		// make upper case
		if (islower(userInput))
		{
			userInput = toupper(userInput);
		}


		switch (userInput)
		{
		case 'Y':
			continueGame = true;
			isRepeat = false;

			resetGame();
			break;

		case 'N':
			continueGame = false;
			isRepeat = false;
			break;

		default:
			// if the number entered is incorrect
			cout << endl;
			cout << "Menu letter " << userInput << " does not exist" << endl;

			display->tryAgain();
			break;
		}
	}

	return continueGame;
}
