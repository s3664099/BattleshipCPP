#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include "board.cpp"
#include "display.cpp"
#include "controller.cpp"
#include "action.cpp"
using namespace std;

//Action

int boardSize = 10;
bool skipTurn = false;

void set_up();
void start_game(Board *opponent01,Board *opponent02 ,int players);
void showGrid(int boardSize,Board *firstShot,Board *secondShot, Board* opponent01,Board* opponent02, int players);
int turn(Board *defender, Board* attacker,bool skipTurn);

int main() {
	set_up();
	return 0;
}

void set_up() {

	int players = getNumber("Please enter the number of players (0,1,2)",0,2);

	//Set up the boards
	Board *opponent01 = new Board("Marvin", boardSize);
	Board *opponent02 = new Board("Deep Thought", boardSize);

	//Place the ships
	if (players == 0) {
		opponent01->addShips();
		opponent02->addShips();
	} else if (players == 1) {
		opponent02->addShips();
		addShips(opponent01,1,boardSize-1);
	} else {
		addShips(opponent01,1,boardSize-1);
		addShips(opponent02,2,boardSize-1);
	}

	start_game(opponent01,opponent02,players);
}

void start_game(Board *opponent01,Board *opponent02,int players) {


	std::srand(std::time(0));
	int result = 1;
	int goFirst = rand()%2;
	int turns = 0;
	Board *firstShot;
	Board *secondShot;

	if (players == 0) {
		displayGrids(boardSize,opponent01->getGrid(),opponent02->getGrid());

	    std::chrono::seconds dura( 5);
	    std::this_thread::sleep_for( dura );
	}

	if (goFirst == 0) {
		firstShot = opponent01;
		secondShot = opponent02;
	} else {
		firstShot = opponent02;
		secondShot = opponent01;
	}

	std::cout<<firstShot->getName()<<" goes first"<<std::endl;

	showGrid(boardSize,firstShot,secondShot,opponent01,opponent02,players);

	while (result != 3) {

		turns += 1;

		//Sleeps for 2 seconds
	    //std::chrono::seconds dura( 2);
	    //std::this_thread::sleep_for( dura );

	    result = turn(firstShot,secondShot, skipTurn);

	    if (result != 3) {
	    	if (players == 2) {
	    		displayGrids(boardSize,firstShot->getGrid(),secondShot->getSpotsHit());
	    	}

	    	result = turn(secondShot,firstShot,skipTurn);
	    }

	    showGrid(boardSize,firstShot,secondShot,opponent01,opponent02,players);

	    if (result == 3) {
	    	std::cout<<"Game over in "<<turns<<" turns"<<std::endl;
	    }
	}

}

void showGrid(int boardSize,Board *firstShot,Board *secondShot,Board *opponent01,Board* opponent02, int players) {

	//Sees how many players and displays the appropriate boards
	if (players == 0) {
		displayGrids(boardSize,opponent01->getGrid(),opponent02->getGrid());
	} else if (players == 1) {

		if (firstShot->getManualPlayer()) {
			displayGrids(boardSize,firstShot->getGrid(),secondShot->getSpotsHit());
		} else {
			displayGrids(boardSize,firstShot->getSpotsHit(),secondShot->getGrid());
		}
	} else {
		displayGrids(boardSize,firstShot->getSpotsHit(),secondShot->getGrid());
	}
}

int turn(Board* attacker, Board* defender,bool skipTurn) {

	int result = 0;

	if (!skipTurn) {
		std::cout<<attacker->getName()<<"'s Shot"<<std::endl;

		//Checks whether manual player or not, and if not calls the algorithm
		if (attacker->getManualPlayer()) {
			result = fireShot(defender,attacker,boardSize);
		} else {
			result = fire(defender,attacker);
		}
	}

	skipTurn = false;

	//Checks if the shot was a hit, and sets the skip turn flag
	if (result != 0) {
		skipTurn = true;
	}

	//Checks for win conditions
	if (result == 3) {
		std::cout<<attacker->getName()<<" has won."<<std::endl;
	}

	return result;
}