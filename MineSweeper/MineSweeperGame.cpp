/*
	Details: Main Game File

	Notes: 
	- Make program cleaner
	- Validate all inputs
	- check how many letters i can input when asked for F or D option
	- instructions?

	CURRENTLY WORKING THROUGH THE PROGRAM TRYING TO MAKE IT CLEANER, MORE READABLE AND SLIGHTLY MORE TECHNICAL.
	USING NAMESPACES TO BE MORE ORGANISED AND USING FOR LOOP TECHNIQUES TO MAKE THE PROGRAM MORE USER INTERFACE FRIENDLY.
	SEE CODING STYLE DOCUMENT. HEIGHT AND WIDTH COULD BE INPUT IN THE MINESWEEPER OBJECT AND THEREFORE CHECKED FOR ERRORS.
	ALSO USE TRY AND CATCH FUNCITONS TO CHECK FOR ERRORS

	SHORT INT HAS RANGE FROM -32,768 - 32767 AND IS ONLY 2 BYTES. NORMAL INT RANGES FROM -2MIL TO 2MIL AND IS 4 BYTES

*/

#include "MineSweeperGame.h"

#include <iostream>
#include <string>
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
		System::welcome();					// Print title
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
	coordinates.r = inputCoordR - 1;
	coordinates.c = inputCoordC - 1;
}


/****************************PreGame********************************/

bool MineSweeper::mainMenu()
{
	bool isRepeat = false;
	int userInput = 0;


	// output main menu display
	System::mainMenuInterface();


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
			System::welcome();

			continueGame = loadGame();
			break;

		case 2:
			// clear console and output welcome display
			system("cls");
			System::welcome();

			settingsMenu();

			// output main menu display
			System::mainMenuInterface();
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
			System::tryAgain();

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
	System::settingsInterface();

	
	isRepeat = true;
	while (isRepeat)
	{
		// Prompt for input
		cout << "Selection: ";

		// READ input
		cin >> userInput;


		// SET game mode related to the players choice.
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
			System::tryAgain();
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


	getNumberOfMines();
	
	// clear the console
	system("cls");

	// output the welcome display
	System::welcome();
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

/*************************Functionality*****************************/


/*
Return code (This relates to playGame() and find()) :
0 = Hit Bomb
1 = Valid
2 = Could not be Flagged
3 = Could not be Dug
4 = Invalid Letter
5 = Invalid Coordinates
*/
bool MineSweeper::playGame()
{
	bool inGame = false;
	int returnCode = 0;

	// output instructions display
	System::instructions();


	// Output dependent on number of mines hidden
	if (numberOfMines < 1)
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
		case 0:
			// output looser display
			System::looser();

			// change characters in the visual array at position with mines.
			findMinePositions();

			// display the grid
			visualGrid.displayGrid();

			continueGame = continueOrQuit();

			// break out of loop
			inGame = false;
			break;

			/*1 = VALID INPUT. UNUSED FOR ERROR CHECKING*/

		case 2:
			cout << "Position could not be Flagged. Please check and try again." << endl;
			break;
		case 3:
			cout << "Position could not be Dug. Please check and try again." << endl;
			break;
		case 4:
			cout << "Please select 'F' to Flag/ 'D' to Dig a position" << endl;
			break;

		case 5:
			cout << "Invalid coordinates. Please check and try again." << endl;
			break;

		}
		// update number of correctly flagged mines
		updateCounter();


		// Check if game is won
		if (correctFlags == numberOfMines && totalFlags == numberOfMines)
		{
			System::winner();
			continueGame = continueOrQuit();
			continueGame = false;
		}
	}

	return continueGame;
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
			ErrorHandling::validateHeightWidth(height, width, gameMode);

			// if the input comes back valid
			isValid = true;	
		}
		catch (char n)
		{
			// Print error message
			ErrorHandling::printMessage(n);

			isValid = false;

			// output try agian display
			System::tryAgain();
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

	// print blank lines
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
		cout << endl;
		cout << "Action: ";

		// READ input
		cin >> actionLetter;


		// IF the user input is lower case
		if (islower(actionLetter))
		{
			// Make uppercase
			actionLetter = toupper(actionLetter);
		}


		// Check inputs for errors
		try
		{
			ErrorHandling::validateCoordinates(coordinates.c, coordinates.r,
				actionLetter, height, width);

			// if inputs are valid
			isValid = true;
		}
		catch (int n)
		{
			// if exception is thrown
			isValid = false;

			// Print error message
			ErrorHandling::printMessage(n);

			System::tryAgain();
		}
	} // END while
}



int MineSweeper::actOnCoordInput()
{
	bool isFlagged = false, isSafe = false;
	int returnCode = 0;

	switch (actionLetter)
	{
	case 'F':
		isFlagged = visualGrid.flag(coordinates.c, coordinates.r);

		// position not flagged.
		if (isFlagged == false)
		{
			returnCode = 2;
		}
		break;
	case 'D':
		isSafe = mineGrid.dig(coordinates.c, coordinates.r);

		// Depending on the output of the dig function
		if (isSafe == false)
		{
			// Mine HIT
			returnCode = 0;
		}
		else if (isSafe == true)
		{
			// Position can not be dug
			returnCode = 3;
		}
		else
		{
			// matching variable type.
			changeIntToChar();
		}
		break;

	default:
		// invalid letter
		returnCode = 4;
		break;
	}

	return returnCode;
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


void MineSweeper::changeIntToChar()
{
	int valAtPosition = 0;
	char setChar = '*';

	 
	// get value at mArray position
	valAtPosition = mineGrid.getPos(coordinates.c, coordinates.r);

	switch (valAtPosition)
	{
	case -1:
		setChar = '!';
		break;
	case 0:
		setChar = '0';
		break;
	case 1:
		setChar = '1';
		break;
	case 2:
		setChar = '2';
		break;
	case 3:
		setChar = '3';
		break;
	case 4:
		setChar = '4';
		break;
	case 5:
		setChar = '5';
		break;
	case 6:
		setChar = '6';
		break;
	case 7:
		setChar = '7';
		break;
	case 8:
		setChar = '8';
		break;
	}

	// set position of vArray = to char
	visualGrid.setPos(coordinates.c, coordinates.r, setChar);
}


void MineSweeper::findMinePositions()
{
	int mPos = 0;

	// FOR each position in mine array
	for (int r = 0; r < width; r++)
	{
		for (int c = 0; c < width; c++)
		{
			mPos = mineGrid.getPos(c, r);

			// if position in mArray = -1
			if (mPos == -1)
			{
				// call feedbk function with vArray coords
				changeIntToChar();
			}
		}
	}
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