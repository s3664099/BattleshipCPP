#include <string>
#include <vector>
#include "board.cpp"
//#include "display.cpp"
#include "controller.cpp"

using namespace std;

int boardSize = 10;

void battleship();

int main() {
	set_up();
	return 0;
}

void set_up() {

	int players = getNumber("Please enter the number of players (0,1,2)",0,2);

	//Set up the boards
	Board opponent01 = new Board("Marvin", boardSize);
	Board opponent01 = new Board("Deep Thought", boardSize);

	//Place the ships
	if (players == 0) {
		opponent01.addShips();
		opponent02.addShips();
	} else if (players == 1) {
		opponent02.addShips();
		addShips(opponent01,1,boardSize-1);
	} else {
		addShips(opponent01,1,boardSize-1);
		addShips(opponent02,2,boardSize-1);
	}

}
