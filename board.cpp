#include "board.h"

//Create the potential hits in a set
//Move into a list as pointer
//Destroy the set afterwards

Board::Board(string objectName,int size) {
	this->gridSize = 9;
	this->objectName = objectName;
	this->rows = size;
	this->grid = std::vector<std::vector<std::string>>(size, std::vector<std::string>(size, "."));
	this->spotsHit = grid = std::vector<std::vector<std::string>>(size, std::vector<std::string>(size, "."));

	ships->emplace(4,'e',"Aircraft Carrier");
	ships->emplace(4,'d',"BattleShip");
	ships->emplace(3,'b',"Submarine");
	ships->emplace(3,'c',"Cruiser");
	ships->emplace(2,'a',"Destroyer");
}

string Board::getName() {
	return this->objectName;
}

int Board::getSize() {
	return this->rows;
}

void Board::setName(string objectName) {
	this->objectName = objectName;
}

std::vector<std::vector<std::string>> Board::getGrid() {
	return this->grid;
}

std::vector<std::vector<std::string>> Board::getSpotsHit() {
	return this->spotsHit;
}

set<Coordinate> Board::getPotentialShots() {
	return this->potentialShots;
}

void Board::setPotentialShots(set<Coordinate> potentialShots) {
 	this->potentialShots = potentialShots;
}

set<int> Board::getShipShots() {
	return this->shipShots;
}

void Board::setShipShots(set<int> shipShots) {
	this->shipShots = shipShots;
}

//Getters & Setters for the hits
void Board::setHitShip(int hitShip) {
	this->hitShip = hitShip;
}

int Board::getHitShip() {
	return this->hitShip;
}

void Board::setHit(Coordinate hit) {
	this->hit = hit;
}

Coordinate Board::getHit() {
	return this->hit;
}

//Sets the movement the computer will go on if a ship has been his more than once
void Board::setMovement(int movement) {
	this->movement = movement;
}

int Board::getMovement() {
	return this->movement;
}

void Board::setOriginalHit(Coordinate originalHit) {
	this->originalHit = originalHit;
}

Coordinate Board::getOriginalHit() {
	return this->originalHit;
}

set<Ship>* Board::getShips() {
	return this->ships;
}

void Board::setManualPlayer(){
	this->manualPlayer = true;
}

bool Board::getManualPlayer(){
	return this->manualPlayer;
}

void Board::addShips() {

	int code = 0;

	//Goes through each of the ships and adds them to the board
	for (Ship ship:*(this->ships)) {
		printf("%s %d %c/n",ship.getName().c_str(),ship.getLength(),ship.getLetter());
		addShip(ship);
		code++;
	}
}

void Board::addShip(Ship ship) {
	int length = ship.getLength();
	char code = ship.getLetter();

	//Creates a set to hold the potential places the ship can be placed
	set<Coordinate> potentialPlace;

	//Selects a random angle for the ship (0 = Across, 1 = Down)
	int angle = rand()%2;

	//If the angle is vertical
	int shipLenX = 0;
	int shipLenY = length;
	int posX = 0;
	int posY = 1;

	if (angle == 1) {
		shipLenX = length;
		shipLenY = 0;
		posX = 1;
		posY = 0;
	}

	//Gets a list of potential places to place the ship
	potentialPlace = selectPlaces(shipLenX,shipLenY,potentialPlace,length,angle);

	//Checks if the size is 0, and if it is, builds the set from the other angle
	if (potentialPlace.size()<1) {
		potentialPlace = selectPlaces(shipLenY,shipLenX,potentialPlace,length,angle);
	}

	int number = rand()%potentialPlace.size();
	int it = 0;
	int shipX = 0;
	int shipY = 0;

	for (Coordinate place:potentialPlace) {
		if (it == number) {
			shipX = place.getX();
			shipY = place.getY();
		}
		it ++;
	}

	placeShip(ship,shipX,shipY,posX,posY,length,code,angle);


}


/*
		set<Coordinate> selectPlaces(int left, int down, set<Coordinate> potentialPlace, int length, int angle);
		string[][] placeShip(Ship ship, int shipX, int shipY, int posX, int posY, int length, string code, int angle);
		int checkWhichShip(Coordinate coOrds, string playerName);
		Ship checkShipHit(Coordinate coOrds, string playerName);
		void removeShip(Ship shipToRemove);
		bool checkRemainingShips();
		void markGrid(set<Coordinate> sectionsToMark);
		void testSinkShip(string playerName);
	*/