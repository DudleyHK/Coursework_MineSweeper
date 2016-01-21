/*




*/
#include <string>
using namespace std;

namespace ErrorHandling
{
	// int errorNumber; // THIS IS NOT LIKED BY THE COMPILER ? WHY?

	void validateHeightWidth(string &input, char gameMode);
	void validateMenuSelection(string &input);
	void printMessage(char errorNumber);
}