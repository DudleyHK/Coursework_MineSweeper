/*
	Solution: System
	Author: Dudley Dawes
	Summary: This class is used to output user interface displays.
*/

#include <iostream>
using namespace std;


class Display
{
public:

	Display();
	~Display();


	void winner();
	void looser();
	void welcome();
	void instructions();
	void settingsInterface();
	void mainMenuInterface();
	void tryAgain();
};