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

	validateUserInput = NULL;

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


	// Display main Menu
	System::mainMenuInterface();

	// RUN loop until input is valid
	isRepeat = true;
	while (isRepeat)
	{
		int menuValue = 0;

		cout << "Selection: ";

		// Read user input
		cin.getline(validateUserInput, strlen(validateUserInput));

		// return TRUE if input is valid
		isValid = menuValidator();

		// IF input is correct
		if (isValid == true)
		{
			// RUN statement
			switch (convertedValue)
			{
			case 1:
				// IF difficultly mode has NOT been selected
				if (gameMode ==  -1)
				{
					// SET default mode and values
					gameMode = 0;

					height = settings.getDefaultHeight();	// Use DEFAULT height
					width = settings.getDefaultWidth();		// Use DEFAULT width
					
				}

				getNumberOfMines();
				
				system("cls");				// Clear console
				System::welcome();			// Print title
				continueGame = loadGame();	// Load game

				break;

			case 2:
				system("cls");				// Clear console
				System::welcome();			// Display title
				gameMode = settingsMenu();	// Go to the settingsMenu

				System::mainMenuInterface();// Display main menu options 
				break;

				
			case 3:
				// IF players wishes to quit game
				continueGame = false;
				break;


			default:
				// final check incase user has entered one invalid number
				cout << endl;
				cout << "Menu value " << menuValue << " does not exist" << endl;
				System::tryAgain();	

				break;

			} // END userInput switch
		}
		else
		{
			System::tryAgain();
		}


		// IF variable is false
		if (continueGame == false)
		{
			// break loop to exit
			isRepeat = false;
		}
	} // END menu loop


	return continueGame;
}

int MineSweeper::settingsMenu()
{
	// declare variables
	bool isRepeat = false;

	// display the menu
	System::settingsInterface();


	// Run loop until user input is valid
	isRepeat = true;
	while (isRepeat)
	{
		int settingsValue = 0;

		cout << "Selection: ";

		// READ input
		cin.getline(validateUserInput, strlen(validateUserInput));

		// return TRUE if input is valid
		isValid = menuValidator();

		// If no error are detected
		if (isValid == true)
		{
			// RUN statement
			switch (convertedValue)
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
				// final check incase user has entered invalid numerical value
				cout << endl;
				cout << "Menu value " << settingsValue << " does not exist" << endl;
				System::tryAgain();
				break;

			}// END switch
		}
		else
		{
			System::tryAgain();
		}
	}// END menu loop


	// IF default has NOT been selected
	if (gameMode != 0)
	{
		inputGridSize();				// USER INPUT size
	}
	else
	{
		height = settings.getDefaultHeight();	// Use DEFAULT height
		width = settings.getDefaultWidth();		// Use DEFAULT width
	}

	getNumberOfMines();


	
	system("cls");			// Clear console
	System::welcome();		// Reprint Welcome message


	return gameMode;
}


/*This function sets and initialise the objects/ variables need to run the game.
Including passing variable to the visual and mine objects. Initialsing both objects 
arrays, assigning mines random positions and finally runnning the game.*/
bool MineSweeper::loadGame()
{
	passSize();
	mineGrid.initialiseArray();
	mineGrid.placeMines();
	visualGrid.initialiseArray();

	continueGame = playGame();

	return continueGame;
}

/*************************Functionality*****************************/


/*
Return Key (This relates to playGame() and find()) :
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
	int valInput = 1;
	

	cout << "There are " << numberOfMines << " mines hidden. Enjoy :) :)" << endl;
	cout << "-----------------------------------------" << endl;

	inGame = true;

	while (inGame)
	{
		visualGrid.displayGrid();
		valInput = guessPosition();


		// check validation options
		if (valInput != 1)
		{
			switch (valInput)
			{

			case 0: 
				cout << "BOOOOOOOOM.. OOps. YOU LOOSE.." << endl;
				findMinePositions();
				visualGrid.displayGrid();

				continueGame = continueOrQuit();
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
		}
		else
		{
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
	}
	
	return continueGame;
}


void MineSweeper::inputGridSize()
{
	bool isRepeat = false;

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
			// Print error message and SET isValid to falase;
			ErrorHandling::printMessage(n);
			isValid = false;
			System::tryAgain();
		}

		// IF isValid is TRUE exit loop
		if (isValid == true)
		{
			isRepeat = false;
		}

	}// END while
}


int MineSweeper::guessPosition()
{
	int fVal = 1, isSafe = 1, v = 1;
	char charInput = '*';
	bool inputValid = false;

	cout << "Please enter coordintes and option:" << endl;
	cin >> validateUserInput;

	/*****VALIDATE USER INPUT*****/



	// create coords to be used by the program.
	createNewCoords();

	// make upper case
	if (islower(charInput))
	{
		charInput = toupper(charInput);
	}

	switch (charInput)
	{
	case 'F':
		fVal = visualGrid.flag(coordinates.c, coordinates.r);

		// position not flagged.
		if (fVal == 0)
		{
			v = 2;
		}

		break;
	case 'D':
		isSafe = mineGrid.dig(coordinates.c, coordinates.r);


		if (isSafe == -1)
		{
			// hit Bomb :S oops
			v = 0;
		}
		else if (isSafe == 0)
		{
			v = 3;
		}
		else
		{
			// select char to display
			changeIntToChar();

			break;
	default:
		// char is invalid.
		v = 4;
		break;
		}
	}

	return v;
}

/*Check each element of the grids to check the number of total flags on the map, 
and the number of flags correctly positioned on the map. This will avoid players
being able to cheat by randomly placing 10 flags in the grid*/
void MineSweeper::updateCounter()
{
	//char vPos = '*';
	//int mPos = 0;
	int totalFlagsCounter = 0, correctFlagsCounter = 0;

	// 
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


/*This function only works when only ONE NUMERICAL output is needed.*/
bool MineSweeper::menuValidator()
{
	convertedValue = 0;

	try
	{
		ErrorHandling::validateMenuSelection(validateUserInput);

		// if the input comes back valid
		convertedValue = stoi(validateUserInput);			// convert string to int					
		isValid = true;										// SET isValid to TRUE
	}
	catch (char n)
	{
		// Print error message and SET isValid to falase;
		ErrorHandling::printMessage(n);
		isValid = false;
	}

	cin.clear();

	return isValid;
}