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
	// cerate instance of the mineSweeper class.
	MineSweeper msGame;

	bool continueGame = true;
	bool gameLoop = false;


	gameLoop = true;

	while (gameLoop)
	{
		Display::welcome();					// Print title
		continueGame = msGame.mainMenu();	// Goto MainMenu


		// IF the player wishes to exit the game
		if (continueGame == false)
		{
			// break out of the loop
			gameLoop = false;
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

MineSweeper::~MineSweeper()
{
}

/* return default setting if game mode is 0. Else calculate number of mines 
based on the difficult mode.*/
void MineSweeper::getNumberOfMines()
{
	int area = height * width;


	numberOfMines = settings.getNumberOfMines(area, gameMode);
}

/*Pass Height, Width and Number of Mines to the Mine Grid and Visual Grid*/
void MineSweeper::passSize()
{
	mineGrid.setSize(height, width, numberOfMines);
	visualGrid.setSize(height, width, numberOfMines);
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
	Display::mainMenuInterface();


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

			// clear console and output welcome display
			system("cls");
			Display::welcome();

			// go to:
			continueGame = loadGame();
			break;

		case 2:
			// clear console and output welcome display
			system("cls");
			Display::welcome();

			// go to: 
			settingsMenu();

			// output main menu display
			Display::mainMenuInterface();
			break;

		case 3:
			// break loop and quit program
			isRepeat = false;
			break;

		default:
			// if the number entered is incorrect
			cout << endl;
			cout << "Menu value " << userInput << " does not exist" << endl;

			// output try again display
			Display::tryAgain();

			break;

		} // END userInput switch

		// IF player wishes to quit the game
		if (continueGame == false)
		{
			// break loop
			isRepeat = false;
		}
	} // END menu loop

	
	return continueGame;
}


void MineSweeper::settingsMenu()
{
	bool isRepeat = false;
	int userInput = 0;

	// output the settings menu display
	Display::settingsInterface();

	
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
			Display::tryAgain();
			break;

		}// END switch
	}// END menu loop


	// IF game mode is NOT default
	if (gameMode != 0)
	{
		// go to:
		inputGridSize();
	}
	else
	{
		// Grab default values
		height = settings.getDefaultHeight();
		width = settings.getDefaultWidth();		
	}

	// go to:
	getNumberOfMines();
	
	// clear the console
	system("cls");

	// output the welcome display
	Display::welcome();
}


/*This function sets and initialise the objects/ variables need to run the game.
Including passing variable to the visual and mine objects. Initialsing both objects 
arrays, assigning mines random positions and finally runnning the game.*/
bool MineSweeper::loadGame()
{
	// pass variables to the mine and visual object
	passSize();
	
	// initialise mine and visual array
	mineGrid.initialiseArray();
	visualGrid.initialiseArray();

	// randomly place mines
	mineGrid.placeMines();


	continueGame = playGame();

	return continueGame;
}

/***************************Run Time*******************************/

bool MineSweeper::playGame()
{
	bool inGame = false;
	int returnCode = 0;
	int numOfMinesDisplayed = 0;
	int mine = -1;

	// output instructions display
	Display::instructions();

	// Output dependent on number of mines hidden
	if (numberOfMines > 1)
	{
		cout << numberOfMines << " mines are hidden." << endl;
	}
	else
	{
		cout << numberOfMines << " mine is hidden." << endl;
	}

	// Print blank lines
	cout << endl << endl;


	inGame = true;
	while (inGame)
	{
		// output the visual grid.
		visualGrid.displayGrid();

		// guess coordinates
		inputCoordinates();

		// act upon user input
		returnCode = actOnCoordInput();


		switch (returnCode)
		{
		case 0:	/*IF PLAYER HAS HIT A MINE*/

			// output looser display
			Display::looser();

			// WHILE the number of mines displayed is NOT equal to the amount of mines
			while (numOfMinesDisplayed <= numberOfMines)
			{
				// update visual grids array.
				visualGrid.changeIntToChar(systemColCoord, systemRowCoord, mine);
				
				// Plus one to counter
				numOfMinesDisplayed++;
			}


			// display the grid
			visualGrid.displayGrid();

			// go to:
			continueGame = continueOrQuit();

			// break out of loop
			inGame = false;
			break;

			/*1 = VALID INPUT. UNUSED FOR ERROR CHECKING*/

		case 2: /*IF LETTER OPTION IS UNAVAILABLE*/

			cout << "option unavailable. please check and try again" << endl;
			cout << "---------------------------------------" << endl;
			break;

		case 3: /*GOTO MAIN MENU OPTIONS*/
			continueGame = true;

			// break out of the function, bypassing other options.
			return continueGame;

			break;
		}

		// update number of correctly flagged mines
		updateCounter();

		// Check if game is won
		if (correctFlags == numberOfMines && totalFlags == numberOfMines)
		{
			Display::winner();
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


	// depending on the letter option
	switch (actionLetter)
	{
	case 'F':
		// if its possible flag the position
		isFlagged = visualGrid.flag(systemColCoord, systemRowCoord);

		if (isFlagged == false)
		{
			// option unavailable
			returnCode = 2;
		}
		break;

	case 'D':
		// check position
		isSafe = mineGrid.dig(systemColCoord, systemRowCoord);

		// If the position is a mine
		if (isSafe == false)
		{
			returnCode = 0;
		}
		else if (isSafe == true)
		{
			// option unavailable
			returnCode = 2;
		}
		else
		{
			// GET the position and display its value.
			valueAtPos = mineGrid.getPos(systemColCoord, systemColCoord);

			// change the visual array.
			visualGrid.changeIntToChar(systemColCoord, systemRowCoord, valueAtPos);
		}
		break;

	// Go back to main menu
	case 'Q':
		returnCode = 3;
		break;
	}
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

		cout << "Height: ";
		cin >> height;

		cout << "Width: ";
		cin >> width;

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
			// Print error message
			errorHandling.printMessage(n);

			isValid = false;

			// output try agian display
			Display::tryAgain();
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
		cin >> inputCoordR;
		cin >> inputCoordC;


		// Call function to minus one from each coordinte input
		createNewCoords();


		// prompt for action
		cout << "Action: ";

		// READ input
		cin >> actionLetter;

		cout << endl;

		// IF the user input is lower case
		if (islower(actionLetter))
		{
			// Make uppercase
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
			Display::tryAgain();
		}
	} // END while

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
			int vPos = visualGrid.getPos(col, row);
			int mPos = mineGrid.getPos(col, row);

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


bool MineSweeper::continueOrQuit()
{
	char userInput = 'Y';
	bool loop = false;

	loop = true;

	while (loop)
	{
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
			loop = false;

			// delete the memory 
			mineGrid.~MGrid();
			visualGrid.~VGrid();

			system("cls");
			welcome();

			break;

		case 'N':
			continueGame = false;
			loop = false;
			break;

		default:
			cout << "Invalid input. Please check and try again :)" << endl;
			break;
		}
	}
	return continueGame;
}