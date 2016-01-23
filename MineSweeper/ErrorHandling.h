/*




*/
#include <string>
using namespace std;

namespace ErrorHandling
{
	void validateHeightWidth(int height, int width, int gameMode);
	void validateCoordinates(int coordCol, int coordRow, char actionLetter,
		int height, int width);
	void printMessage(int errorNumber);
}