/*
	Solution: Mine Sweeper Game	
	Author: Dudley Dawes
	Summary: Class Functions and compliers start point main().
*/

#include "MineSweeperGame.h"

#include <iostream>
using namespace std;


/**START**/
int main()
{
	// create new istances of ojects in heap
	MineSweeper *msGame = new MineSweeper;
	Display display;

	bool continueGame = true;
	bool gameLoop = false;


	gameLoop = true;

	while (gameLoop)
	{
		// output display and call function
		display.welcome();	
		continueGame = msGame->mainMenu();	


		// IF the player wishes to exit the game
		if (continueGame == false)
		{
			// break out of the loop
			gameLoop = false;

			// delete the memory to avoid errors
			delete msGame;
		}
	} // END loop

	return 0;
}


/**************************Data Access******************************/

MineSweeper::MineSweeper()
	: gameMode(-1),
	continueGame(true)
{
	// constuctor
}

/* return default values if game mode is 0. Else calculate number of mines 
based on the difficult mode.*/
void MineSweeper::getNumberOfMines()
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


	// output main menu display
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
			mainMenuPlayGame();
			break;

		case 2:
			displaySettingsMenu();
			break;

		case 3:
			// break loop and quit program
			isRepeat = false;
			continueGame = false;
			break;

		default:
			menuValueIsInvaild(userInput);

			break;

		} // END userInput switch

		isRepeat = mainMenuIsExit();

	} // END menu loop

	
	return continueGame;
}


void MineSweeper::mainMenuPlayGame()
{
	// IF game mode has NOT been selected
	if (gameMode == -1)
	{
		// SET default mode
		gameMode = 0;

		// return DEFAULT values from the settings object
		height = settings.getDefaultHeight();
		width = settings.getDefaultWidth();
	}

	getNumberOfMines();

	// clear console
	system("cls");

	// output welcome display
	display->welcome();

	continueGame = loadGame();
}


void MineSweeper::displaySettingsMenu()
{
	// clear console and output welcome display
	system("cls");
	display->welcome();

	settingsMenu();

	display->mainMenuInterface();
}


bool MineSweeper::mainMenuIsExit()
{
	bool isRepeat = true;

	if (continueGame == false)
	{
		// break loop
		isRepeat = false;
	}

	return isRepeat;
}


void MineSweeper::menuValueIsInvaild(int userInput)
{
	// if the number entered is incorrect
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
		// Grab default values
		height = settings.getDefaultHeight();
		width = settings.getDefaultWidth();		
	}

	getNumberOfMines();
	
	// clear the console
	system("cls");

	// output the welcome display
	display->welcome();
}


/*This function sets and initialise the objects/ variables needed to run the game.*/
bool MineSweeper::loadGame()
{
	// pass variables to the Mine Grid and Visual Grid
	passSize();
	
	// initialise both arrays
	mineGrid->initialiseArray();
	visualGrid->initialiseArray();


	continueGame = playGame();

	return continueGame;
}

/***************************Run Time*******************************/

bool MineSweeper::playGame()
{
	bool inGame = false;
	int mine = -1;

	// SET unused value
	returnCode = 5;


	// output instructions display
	display->instructions();


	// Output dependent on number of mines hidden
	if (numberOfMines > 1)
	{
		cout << numberOfMines << " mines are hidden." << endl;
	}
	else
	{
		cout << numberOfMines << " mine is hidden." << endl;
	}


	inGame = true;
	while (inGame)
	{
		// Print a line.
		cout << endl;
		cout << "===============================================" << endl << endl;

		// output the visual grid.
		visualGrid->displayGrid();

		mineGrid->displayGrid();

		inputCoordinates();

		switch (returnCode)
		{
		case -1:
			playGameIsHit();		
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


void MineSweeper::playGameIsHit()
{
	int numOfMinesDisplayed = 0;

	// WHILE the number of mines displayed is NOT equal to the amount of mines
	while (numOfMinesDisplayed <= numberOfMines)
	{
		// Find each mine in the grid and set visual array
		locateAllMines();

		numOfMinesDisplayed++;
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

	// Prompt for input
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


	// print blank line
	cout << endl << endl;

	// while the input isnt valid
	while (!isValid)
	{
		// Prompt for coordinates
		cout << "Coordinates: ";

		// READ input
		cin >> inputCoordC;
		cin >> inputCoordR;


		// Call function to minus one from each coordinte input
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
	bool isFlagged = false, isSafe = false;


	// depending on the letter option
	switch (actionLetter)
	{
	case 'F':

		// if its possible flag the position
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

	// return values at position
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
			// change the visual array.
			visualGrid->changeIntToChar(systemColCoord, systemRowCoord, valueAtPos);
		}
	}

	return returnCode;
}


bool MineSweeper::checkIfPlayerWon()
{
	bool inGame = true;

	if (returnCode != 1)
	{
		// update number of correctly flagged mines
		updateCounter();

		if (correctFlags == numberOfMines && totalFlags == numberOfMines)
		{
			display->winner();

			continueGame = continueOrQuit();

			inGame = false;
		}
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
			// GET values at each position of the grid for both objects
			char vPos = visualGrid->getPos(col, row);
			int mPos = mineGrid->getPos(col, row);

			if (vPos == 'F')
			{
				// increment total number of mines in grid by one
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

	for (int r = 0; r < width; r++)
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

			// output try again display
			display->tryAgain();
			break;
		}
	}
	return continueGame;
}
