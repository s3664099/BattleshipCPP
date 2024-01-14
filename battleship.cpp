#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include "board.cpp"
#include "display.cpp"
#include "controller.cpp"
using namespace std;

int boardSize = 10;

void set_up();
void start_game(Board *opponent01,Board *opponent02 ,int players);
void showGrid(int boardSize,Board *firstShot,Board *secondShot, Board* opponent01,Board* opponent02, int players);

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
	bool skipTurn = false;
	int goFirst = rand()%2;
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
}
	/*

		System.out.printf("%s goes first%n",firstShot.getName());
		
		showGrid(boardSize,firstShot,secondShot,players);
		
		while (result != 3) {
			
			turns += 1;
			
			//Sleeps for 2 seconds
			try {
				TimeUnit.SECONDS.sleep(2);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			result = turn(firstShot,secondShot);
			
			if (result !=3) {
				
				if (players == 2) {
					display.displayGrids(boardSize,firstShot.getGrid(),secondShot.getSpotsHit());
				}
				
				result = turn(secondShot,firstShot);
			}
			
			showGrid(boardSize,firstShot,secondShot,players);
			
			if (result == 3) {
				System.out.printf("Game over in %s turns%n",turns);
			}			
		}
	}
	*/

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

	/*		
	private int turn(Board defender, Board attacker) {
		
		result = 0;
		
		if (!skipTurn) {
			System.out.printf("%s's Shot%n",attacker.getName());
			
			//Checks whether a manual player or not, and if not calls the algorith
			if (attacker.getManualPlayer()) {
				result = controller.fireShot(defender,attacker,boardSize);
			} else {
				result = action.fire(defender,attacker);
			}
		}
		
		skipTurn = false;
		
		//Checks if the shot was a hit, and sets the skip turn flag
		if (result != 0) {
			skipTurn = true;
		}
		
		//Checks for a win conditions
		if (result == 3) {
			System.out.printf("%s has won%n",attacker.getName());
		}
		
		return result;
	}
}

	*/