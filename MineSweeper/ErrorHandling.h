/*




*/
#include <string>
using namespace std;

namespace ErrorHandling
{
	// int errorNumber; // THIS IS NOT LIKED BY THE COMPILER ? WHY?

	void validateHeightWidth(int height, int width, char gameMode);
	void validateMenuSelection(string &input);
	void printMessage(char errorNumber);
}