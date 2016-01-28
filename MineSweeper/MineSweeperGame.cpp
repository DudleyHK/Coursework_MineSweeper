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
	// cerate new istances of boject in heap
	MineSweeper *msGame = new MineSweeper;
	Display display;

	bool continueGame = true;
	bool gameLoop = false;


	gameLoop = true;

	while (gameLoop)
	{
		display.welcome();					// Print title
		continueGame = msGame->mainMenu();	// Goto MainMenu


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
{
	// SET game mode variable as UNUSED
	gameMode = -1;
	continueGame = true;
}

/* return default values if game mode is 0. Else calculate number of mines 
based on the difficult mode.*/
void MineSweeper::getNumberOfMines()
{
	int area = height * width;

	// return value
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
		// Prompt for input
		cout << "Selection: ";

		// READ input
		cin >> userInput;

	
		switch (userInput)
		{
		case 1:
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
			break;

		case 2:
			// clear console and output welcome display
			system("cls");
			display->welcome();

			settingsMenu();

			// output main menu display
			display->mainMenuInterface();
			break;

		case 3:
			// break loop and quit program
			isRepeat = false;
			continueGame = false;
			break;

		default:
			// if the number entered is incorrect
			cout << endl;
			cout << "Menu value " << userInput << " does not exist" << endl;

			// output try again display
			display->tryAgain();

			break;

		} // END userInput switch

		// IF player wishes to quit the game
		if (continueGame == false)
		{
			// break loop
			isRepeat = false;

			// delete allocated memory
			delete mineGrid;
			delete visualGrid;
			delete display;
		
		}
	} // END menu loop

	
	return continueGame;
}


void MineSweeper::settingsMenu()
{
	bool isRepeat = false;
	int userInput = 0;

	// output the settings menu display
	display->settingsInterface();

	
	isRepeat = true;
	while (isRepeat)
	{
		// Prompt for input
		cout << "Selection: ";

		// READ input
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
			// if the number entered is incorrect
			cout << endl;
			cout << "Menu value " << userInput << " does not exist" << endl;
			
			// output try again display
			display->tryAgain();
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


/*This function sets and initialise the objects/ variables need to run the game.
Including passing variable to the visual and mine objects. Initialsing both objects 
arrays, assigning mines random positions and finally runnning the game.*/
bool MineSweeper::loadGame()
{
	// pass variables to the mine and visual object
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
	int numOfMinesDisplayed = 0;
	int mine = -1;

	// select unused value
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

		// guess coordinates
		inputCoordinates();


		switch (returnCode)
		{
		case -1:	/*IF PLAYER HAS HIT A MINE*/

			// WHILE the number of mines displayed is NOT equal to the amount of mines
			while (numOfMinesDisplayed <= numberOfMines)
			{
				// Find and print each mine in the grid
				locateAllMines();

				// Plus one to counter
				numOfMinesDisplayed++;
			}

			// display the grid
			visualGrid->displayGrid();

			// output looser display
			display->looser();

			continueGame = continueOrQuit();

			// break out of loop
			inGame = false;
			break;

		case 0: /*IF LETTER OPTION IS UNAVAILABLE*/

			cout << "option unavailable. please check and try again" << endl;
			break;

		case 1: /*GOTO MAIN MENU OPTIONS*/

			// clear the console
			system("cls");

			// output welcome display
			display->welcome();

			// output mainmenu display
			display->mainMenuInterface();

			// delete object and array memory
			mineGrid->~MGrid();
			visualGrid->~VGrid();

			// break out of loop
			inGame = false;
		}

		// update number of correctly flagged mines
		updateCounter();

		// Check if game is won
		if (correctFlags == numberOfMines && totalFlags == numberOfMines)
		{
			// output display
			display->winner();

			continueGame = continueOrQuit();

			continueGame = false;
		}
	}

	return continueGame;
}

void MineSweeper::actOnCoordInput()
{
	bool isFlagged = false, isSafe = false;
	int valueAtPos = 0;
	char characterAtPos = '*';


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

		// Check if position is a mine
		valueAtPos = mineGrid->getPos(systemColCoord, systemRowCoord);

		// if position is a mine
		if (valueAtPos == -1)
		{
			returnCode = -1;
		}
		else
		{
			// check if position is an 'F'
			characterAtPos = visualGrid->getPos(systemColCoord, systemRowCoord);

			if (characterAtPos != 'F')
			{
				// check position
				mineGrid->dig(systemColCoord, systemRowCoord);

				// GET the position and display its value.
				valueAtPos = mineGrid->getPos(systemColCoord, systemColCoord);

				// change the visual array.
				visualGrid->changeIntToChar(systemColCoord, systemRowCoord, valueAtPos);
			}
		}
		break;

	case 'Q':
		returnCode = 1;

		break;
	}
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


		// Check for errors
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

			// output try agian display
			display->tryAgain();
		}

		// IF isValid is TRUE exit loop
		if (isValid == true)
		{
			isRepeat = false;
		}

	}// END while
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


		// prompt for action
		cout << "Action: ";

		// READ input
		cin >> actionLetter;

		// next line
		cout << endl;

		// IF the user input is lower case. Make uppercase
		if (islower(actionLetter))
		{
			actionLetter = toupper(actionLetter);
		}


		// check for errors
		try
		{
			// go to:
			errorHandling.validateCoordinates(systemColCoord, systemRowCoord,
				actionLetter, height, width);

			// if all inputs are valid
			isValid = true;
		}
		catch (int n)
		{
			// if exception is thrown
			isValid = false;

			// Print error message
			errorHandling.printMessage(n);

			// go to:
			display->tryAgain();
		}
	} // END while

	// go to:
	actOnCoordInput();
}


/*Check each element of the grids to check the number of total flags on the map, 
and the number of flags correctly positioned on the map. This will avoid players
being able to cheat by randomly placing 10 flags in the grid*/
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


/*This functions locates each mine in the number grid and sends the coordinates
 of the position along with the number to the visual grid to be input into the
 array.*/
void MineSweeper::locateAllMines()
{
	int valueAtPos = 0;

	// FOR each position in mine array
	for (int r = 0; r < width; r++)
	{
		for (int c = 0; c < width; c++)
		{
			valueAtPos = mineGrid->getPos(c, r);

			// if position in mArray = -1
			if (valueAtPos == -1)
			{
				// call feedbk function with vArray coords
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
		// prompt for input
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
			// go back to main menu
			continueGame = true;
			isRepeat = false;

			// delete the memory 
			mineGrid->~MGrid();
			visualGrid->~VGrid();

			// clear the console
			system("cls");

			// output welcome display
			display->welcome();

			// output main menu display
			display->mainMenuInterface();

			break;

		case 'N':
			// break loops and quit
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