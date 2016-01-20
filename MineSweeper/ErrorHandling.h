/*




*/
#include <string>
using namespace std;

namespace ErrorHandling
{
	// int errorNumber; // THIS IS NOT LIKED BY THE COMPILER ? WHY?

	int checkHeightWidth(string &input, int gameMode);
	void checkOptionSelect(string &input);
	void printMessage(int errorNumber);
}