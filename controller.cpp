#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

int getNumber(string query,int min, int max);
void addShips(Board *user,int num, int boardSize);
int getAngle();
int fireShot(Board* defender, Board* attacker, int boardSize);

int getNumber(string query,int min, int max) {

	bool correct = false;
	int response = 0;

	while (!correct) {

		std::cout<<query<<": ";
		std::cin>>response;
		std::cout<<endl;

		if (cin.fail()) {

		    // user didn't input a number
		    cin.clear(); // reset failbit
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout<<"Please enter a number"<<std::endl;

		} else if ((response > max) || (response < min)) {
			std::cout<<"Please enter a number between "<<min<<" and "<<max<<std::endl;
		} else {
			correct = true;
		}
		
	}

	return response;
}

//Process to add ships for a manual player
void addShips(Board *user,int num,int boardSize) {

	std::vector<Ship>* ships = user->getShips();
	user->setManualPlayer();

	//Sets up the player's name
	std::string playerNumber = "one";
	if (num == 2) {
		playerNumber = "two";
	}
	std::string userName = "";
	std::cout<<"Please enter player "<<playerNumber<<"'s name: ";
	std::cin>>userName;

	//Has the player entered a name?
	if (userName.length()<1) {
		if(num == 1) {
			userName = "Nameless Player";
		} else {
			userName = "Player without a Name";
		}
	}

	user->setName(userName);

	//Process to add ships
	for (Ship ship:*ships) {

		//Creates a set to hold the potential places the ship can be placed
		set<Coordinate> potentialPlace;

		displayGrid(10,user->getGrid());

		std::cout<<"Placing the "<<ship.getName()<<std::endl;
		int length = ship.getLength();
		char code = ship.getLetter();

		//If the angle is vertical
		int shipLenX = 0;
		int shipLenY = length;
		int posX = 0;
		int posY = 1;

		int angle = getAngle();

		if (angle == 1) {
			shipLenX = length;
			shipLenY = 0;
			posX = 1;
			posY = 0;
		}

		//Generates a list of potential places
		potentialPlace = user->selectPlaces(shipLenX,shipLenY,potentialPlace,length,angle);
		bool allowable = false;

		while (!allowable) {
			int yPos = getNumber("Enter the x position",0,boardSize);
			int xPos = getNumber("Enter the y position",0,boardSize);

			//Checks if the position is one of the potential places
			for (Coordinate place:potentialPlace) {
				if ((place.getX() == xPos) && (place.getY() == yPos)) {
					allowable = true;
				}
			}

			//If it isn't display potential places
			if (!allowable) {
				std::cout<<"You cannot place the "<<ship.getName()<<" there"<<std::endl;
				std::cout<<"Allowable places"<<std::endl;

				for (Coordinate place:potentialPlace) {
					std::cout<<place.getY()<<" "<<place.getX()<<std::endl;
				} 
			} else {
				user->placeShip(&ship,xPos,yPos,posX,posY,length,code,angle);
			}
		}

		std::cout<<"Press enter to continue";

		// Ignore any remaining characters in the input buffer
    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		// Read a single character (Enter key)
    	char enter;
    	std::cin.get(enter);
    	std::cout<<std::endl;
	}
}

int fireShot(Board* defender, Board* attacker, int boardSize) {
	
	bool alreadyHit = false;

	//Sets the win flag
	int win = 0;

	while(!alreadyHit) {

		//Gets the player's shot
		int xCoord = getNumber("Select Row: ",0,boardSize);
		int yCoord = getNumber("Select Column: ",0,boardSize);

		std::vector<std::vector<std::string>>* spotsHot = defender->getSpotsHit();
		std::vector<std::vector<std::string>>* grid = defender->getGrid();

		//Checks if the player has already fired there
		if (((*grid)[xCoord][yCoord] == "0") || ((*grid)[xCoord][yCoord] == "X")) {
			cout<<"You have already fired a shot there"<<endl;

		//Hits an empty section
		} else if ((*grid)[xCoord][yCoord] == ".") {
			(*grid)[xCoord][yCoord] = "0";
			(*spotsHot)[xCoord][yCoord] = "0";
			alreadyHit = true;

		//Hits occupied section
		} else {
			win = 1;
			(*grid)[xCoord][yCoord] = "X";
			(*spotsHot)[xCoord][yCoord] = "X";
			alreadyHit = true;
		}

		//Determines which ship has been hit, and whether it has been sunk
		if (win == 1) {
			Coordinate coord(xCoord,yCoord);
			win = defender->checkWhichShip(coord,attacker->getName());
		}

	}

	return win;	
}

int getAngle() {

	std::cout<<"Please enter the angle"<<std::endl;
	std::cout<<"0) Across"<<std::endl;
	std::cout<<"1) Down"<<std::endl;
	return getNumber("",0,1);
}