/*
	Details: User interface functions

*/

#include "System.h"

#include <iostream>
using namespace std;


void System::welcome()
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



void System::instructions()
{
	cout << "Select a coordinates (x, y) followed by one of the options below" << endl;
	cout << "/t........................................." << endl;
	cout << "/t:      To Dig coordinates press 'D'     :" << endl;
	cout << "/t:     To Flag coordinates press 'F'     :" << endl;
	cout << "/t: To go back to the Main Menu press 'Q' :" << endl;
	cout << "/t........................................." << endl;
	cout << "__________________________________________________________" << endl;
	cout << endl;

}


void System::winner()
{
	cout << endl;
	cout << "/t:::::::::::::::" << endl;
	cout << "/t::!!YOU WIN!!::" << endl;
	cout << "/t:::::::::::::::" << endl;
	cout << "__________________________________________________________" << endl;
	cout << endl << endl;
}


void System::looser()
{
	cout << endl;
	cout << "/t:::::::::::::::" << endl;
	cout << "/t:( YOU LOOSE ):" << endl;
	cout << "/t:::::::::::::::" << endl;
	cout << "__________________________________________________________" << endl;
	cout << endl << endl;
}



void System::settingsInterface()
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
}


void System::mainMenuInterface()
{
	cout << "MAIN MENU" << endl;
	cout << "----------" << endl << endl;

	cout << "1. Play Game" << endl;
	cout << "2. Settings" << endl;
	cout << "3. Exit" << endl;
}


void System::tryAgain()
{
	cout << "---------------------------------------" << endl;
	cout << "Try again..." << endl;
}