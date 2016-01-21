/*
	Details: Information and functionality commonly used by the program

*/

namespace System
{
	// coordinates used by the computer (user input - 1)
	struct Coordinates
	{
		int r = 0;
		int c = 0;
	};

	// Basic user interface functions
	void winner();
	void looser();
	void welcome();
	void instructions();
	void settingsInterface();
	void mainMenuInterface();
	void tryAgain();

}