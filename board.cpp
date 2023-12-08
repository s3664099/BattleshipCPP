#include "board.h"

Board::Board(string objectName,int size) {
	this->gridSize = 9;
	this->objectName = objectName;
	this->rows = size;
	this->grid = std::vector<std::vector<std::string>>(size, std::vector<std::string>(size, "."));
	this->spotsHit = grid = std::vector<std::vector<std::string>>(size, std::vector<std::string>(size, "."));
	this->ships.insert(Ship ship(4,"e","Aircraft Carrier",
					Ship ship(4,"d","BattleShip"),
					Ship ship(3,"b","Submarine"),
					Ship ship(3,"c","cruiser"),
					Ship ship(2,"a","destroyer")))
}

Board::getName() {
	return this->objectName;
}

Board::getSize() {
	return this->rows;
}

Board::setName(string objectName) {
	this->objectName = objectName;
}

Board::getGrid() {
	return this->grid;
}

Board::getSpotsHit() {
	return this->spotsHit;
}

Board::getPotentialShots() {
	return this->potentialShots;
}

Board::setPotentialShots(set<Coordinate> potentialShots) {
 	this->potentialShots = potentialShots;
}

Board::getShipShots() {
	return this->shipShots;
}


/*

		void setShipShots(set<Integer> shipShots);
		void setHitShip(int hitShip);
		int getHitShip();
		void setHit(Coordinate hit);
		Coordinate getHit();
		void setMovement(int movement);
		int getMovement();
		void setOriginalHit(Coordinate originalHit);
		Coordinate getOriginalHit();
		set<Ship> getShips();
		void setManualPlayer();
		bool getManualPlayer();
		void addShips();
		string[][] addShip(Ship ship);
		int getRandomNumber(int min, int max);
		set<Coordinate> selectPlaces(int left, int down, set<Coordinate> potentialPlace, int length, int angle);
		string[][] placeShip(Ship ship, int shipX, int shipY, int posX, int posY, int length, string code, int angle);
		int checkWhichShip(Coordinate coOrds, string playerName);
		Ship checkShipHit(Coordinate coOrds, string playerName);
		void removeShip(Ship shipToRemove);
		bool checkRemainingShips();
		void markGrid(set<Coordinate> sectionsToMark);
		void testSinkShip(string playerName);
	*/