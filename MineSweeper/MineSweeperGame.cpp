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

*/

#include "MineSweeperGame.h"

#include <iostream>
#include <string>

using namespace System;
using namespace std;


/**START**/
int main()
{
	// cerate instance of the mineSweeper class.
	MineSweeper msGame;

	int continueGame = 1;
	bool gameLoop = false;


	gameLoop = true;

	while (gameLoop)
	{
		System::welcome();					// Print title
		continueGame = msGame.mainMenu();	// Goto MainMenu


		// IF the player wishes to exit the game
		if (continueGame == 0)
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
	// set game mode variable to unused
	gameMode = -1;
	continueGame = 1;
}

MineSweeper::~MineSweeper()
{
}

void MineSweeper::getSize()
{
	height = settings.getHeight();
	width = settings.getWidth();
	numberOfMines = settings.calcMines(gameMode);
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
	System::coordinates.first = inputCoordR - 1;
	System::coordinates.second = inputCoordC - 1;
}


/*************************Functionality*****************************/

int MineSweeper::mainMenu()
{
	int isValid = 1;		// Assume value is correct.
	int userInput = 0;

	bool mainMenuRepeat = false;


	mainMenuRepeat = true;

	// Enter menu loop
	while (mainMenuRepeat)
	{
		cout << "MAIN MENU" << endl;
		cout << "----------" << endl << endl;

		cout << "1. Play Game" << endl;
		cout << "2. Settings" << endl;
		cout << "3. Exit" << endl;
		cout << "Selection: ";

		// Read user input
		cin >> userInput;


		// continue if input is correct
		if (isValid == 1)
		{
			switch (userInput)
			{
			case 1:
				// IF difficultly has not been selected
				if (gameMode == -1)
				{
					//  set default mode
					gameMode = 0;
					settings.setDefault(5, 5, 5);
				}

				getSize();


				system("cls");
				title();
				continueGame = loadGame();
				

				break;
			case 2:
				// clear the screen
				system("cls"); 
				title();
				gameMode = settingsMenu();

				break;
			case 3:
				continueGame = 0;
				break;


			default:
				cout << "Enter value 1 - 3" << endl;
				break;
			} // END userInput switch
		}
		else
		{
			cout << "Invalid input. Please check and try agian." << endl;
		}


		// IF variable is 0
		if (continueGame == 0)
		{
			// break loop to exit
			mainMenuRepeat = false;
		}
	} // END menu loop


	return continueGame;
}

int MineSweeper::settingsMenu()
{
	int userInput = 0;
	bool settingsMenuRepeat = false;


	settingsMenuRepeat = true;

	while (settingsMenuRepeat)
	{
		cout << "SETTINGS MENU" << endl;
		cout << "--------------" << endl << endl;

		cout << "Default: 5 x 5 grid. 5 Mines" << endl << endl;

		cout << "Easy:\tMin 3 x 3. 10% Mines" << endl;
		cout << "Medium: Min 5 x 5. 15% Mines" << endl;
		cout << "Hard:\tMin 8 x 8. 25% Mines" << endl << endl;

		cout << "Max Grid Size: 20 x 20" << endl;
		cout << endl << endl;


		cout << "Select Mode:" << endl;
		cout << "----------" << endl;
		cout << "0. Default Mode" << endl;
		cout << "1. Easy" << endl;
		cout << "2. Medium" << endl;
		cout << "3. Hard" << endl;
		cout << "Selection: ";

		cin >> validateUserInput;

		/**VALIDATE INPUT***/

		switch (userInput)
		{
		case 0:
			gameMode = 0;
			settingsMenuRepeat = false;

			break;

		case 1:
			gameMode = 1;
			settingsMenuRepeat = false;
			break;

		case 2:
			gameMode = 2;
			settingsMenuRepeat = false;
			break;

		case 3:
			gameMode = 3;
			settingsMenuRepeat = false;
			break;

		default:
			cout << "Invaild input." << endl;
			break;

		}// END userInput switch
	}// END menu loop


	if (gameMode != 0)
	{
		inputGridSize();				// USER INPUT size
	}
	else
	{
		settings.setDefaultSize(5, 5);	// Use DEFAULT size
	}

	getSize();


	
	system("cls");			// Clear console
	System::welcome();		// Reprint Welcome message

	return gameMode;
}


/*This function sets and initialise the objects/ variables need to run the game.
Including passing variable to the visual and mine objects. Initialsing both objects 
arrays, assigning mines random positions and finally runnning the game.*/
int MineSweeper::loadGame()
{
	passSize();
	mineGrid.initialiseArray();
	mineGrid.placeMines();
	visualGrid.initialiseArray();

	continueGame = playGame();

	return continueGame;
}


/*
Return Key (This relates to playGame() and find()) :
0 = Hit Bomb
1 = Valid
2 = Could not be Flagged
3 = Could not be Dug
4 = Invalid Letter
5 = Invalid Coordinates
*/
int MineSweeper::playGame()
{
	bool inGame = false;
	int valInput = 1;
	

	cout << "There are " << numberOfMines << " mines hidden. Enjoy :) :)" << endl;
	cout << "-----------------------------------------" << endl;

	inGame = true;

	while (inGame)
	{
		visualGrid.displayGrid();
		valInput = find();


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
				continueGame = gameWon();
				inGame = false;
			}
		}
	}
	
	return continueGame;
}


void MineSweeper::inputGridSize()
{
	bool isRepeat = false;


	isRepeat = true;

	while (isRepeat)
	{
		cout << "Enter Height then Width. ie 5 10" << endl;
		cout << "Size:";

		cin >> validateUserInput;

		/*****VALIDATE INPUT****/

		switch (gameMode)
		{
		case 1:
			if ((height < 3 || height > 20) || (width < 3 || width > 20))
			{
				cout << "Invalid input." << endl;
			}
			else
			{
				isRepeat = false;
			}

			break;

		case 2:
			if ((height < 5 || height > 20) || (width < 5 || width > 20))
			{
				cout << "Invalid input." << endl;
			}
			else
			{
				isRepeat = false;
			}


			break;

		case 3:
			if ((height < 8 || height > 20) || (width < 8 || width > 20))
			{
				cout << "Invalid input." << endl;
			}
			else
			{
				isRepeat = false;
			}

			break;
		}// END switch
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
		fVal = visualGrid.flag(coordinates.first, coordinates.second);

		// position not flagged.
		if (fVal == 0)
		{
			v = 2;
		}

		break;
	case 'D':
		isSafe = mineGrid.dig(coordinates.first, coordinates.second);


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
	int currInt = 0;
	char currChar = '*', vPos = '*';

	 
	// get value at mArray position
	currInt = mineGrid.getPos(coordinates.first, coordinates.second);

	switch (currInt)
	{
	case -1:
		currChar = '!';
		break;
	case 0:
		currChar = '0';
		break;
	case 1:
		currChar = '1';
		break;
	case 2:
		currChar = '2';
		break;
	case 3:
		currChar = '3';
		break;
	case 4:
		currChar = '4';
		break;
	case 5:
		currChar = '5';
		break;
	case 6:
		currChar = '6';
		break;
	case 7:
		currChar = '7';
		break;
	case 8:
		currChar = '8';
		break;
	}

	// set position of vArray = to char
	visualGrid.setPos(coordinates.first, coordinates.second, currentChar);
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


int MineSweeper::continueOrQuit()
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
			continueGame = 1;
			loop = false;

			// delete the memory 
			mineGrid.~MGrid();
			visualGrid.~VGrid();

			system("cls");
			System::welcome();

			break;

		case 'N':
			continueGame = 0;
			loop = false;
			break;

		default:
			cout << "Invalid input. Please check and try again :)" << endl;
			break;
		}
	}
	return continueGame;
}