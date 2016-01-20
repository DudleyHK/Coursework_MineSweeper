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


