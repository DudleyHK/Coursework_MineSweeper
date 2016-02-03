/*
	Solution: Display
	Author: Dudley Dawes
	Summary: Display Functions
*/

#include "Display.h"

#include <iostream>
using namespace std;


Display::Display()
{
	// empty
}

Display::~Display()
{
	//Empty
}


void Display::welcome()
{
	cout << "\t\t :::::::::::::::::::::::" << endl;
	cout << "\t\t :: Mine Sweeper Game ::" << endl;
	cout << "\t\t ::                   ::" << endl;
	cout << "\t\t ::    Dudley Dawes   ::" << endl;
	cout << "\t\t :::::::::::::::::::::::" << endl;
	cout << endl << endl;

	cout << "To start - select a mode or just press play!" << endl << endl;

	cout << "__________________________________________________________" << endl;
	cout << endl << endl << endl;
}




void Display::instructions()
{
	cout << "Select a coordinates (x, y) followed by one of the options below" << endl;
	cout << "\t........................................." << endl;
	cout << "\t:      To Dig coordinates press 'D'     :" << endl;
	cout << "\t: To Flag/ Unflag coordinates press 'F' :" << endl;
	cout << "\t: To go back to the Main Menu press 'Q' :" << endl;
	cout << "\t........................................." << endl;
	cout << "__________________________________________________________" << endl;
	cout << endl << endl;
}



void Display::winner()
{
	cout << endl;
	cout << " :::::::::::::::" << endl;
	cout << " ::!!YOU WIN!!::" << endl;
	cout << " :::::::::::::::" << endl;
	cout << "__________________________________________________________" << endl;
	cout << endl;
}


void Display::looser()
{
	cout << endl;
	cout << " :::::::::::::::" << endl;
	cout << " :( YOU LOOSE ):" << endl;
	cout << " :::::::::::::::" << endl;
	cout << "__________________________________________________________" << endl;
	cout << endl;
}



void Display::settingsInterface()
{
	cout << "SETTINGS MENU" << endl;
	cout << "--------------" << endl << endl;

	cout << "Default: 10 x 10 grid. 10 Mines" << endl << endl;

	cout << "Easy:\tMin 4 x 4. 15% Mines" << endl;
	cout << "Medium: Min 5 x 5. 20% Mines" << endl;
	cout << "Hard:\tMin 8 x 8. 30% Mines" << endl << endl;

	cout << "Max Grid Size: 20 x 20" << endl;
	cout << endl << endl;


	cout << "Select Mode:" << endl;
	cout << "----------" << endl;
	cout << "0. Default Mode" << endl;
	cout << "1. Easy" << endl;
	cout << "2. Medium" << endl;
	cout << "3. Hard" << endl;
}


void Display::mainMenuInterface()
{
	cout << "MAIN MENU" << endl;
	cout << "----------" << endl << endl;

	cout << "1. Play" << endl;
	cout << "2. Settings" << endl;
	cout << "3. Exit" << endl;
}


void Display::tryAgain()
{
	cout << endl;
	cout << "---------------------------------------" << endl; 
	cout << "Try again..." << endl;
}