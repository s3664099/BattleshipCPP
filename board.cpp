#include "board.h"

Board::Board(string objectName,int size) {
	this->gridSize = 9;
	this->objectName = objectName;
	this->rows = size;
	this->grid = std::vector<std::vector<std::string>>(size, std::vector<std::string>(size, "."));
	this->spotsHit = grid = std::vector<std::vector<std::string>>(size, std::vector<std::string>(size, "."));
	this->ships.emplace(4,"e","Aircraft Carrier");
	this->ships.emplace(4,"d","BattleShip");
	this->ships.emplace(3,"b","Submarine");
	this->ships.emplace(3,"c","Cruiser");
	this->ships.emplace(2,"a","Destroyer");
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

set<Ship> Board::getShips() {
	return this->ships;
}

void Board::setManualPlayer(){
	this->manualPlayer = true;
}

bool Board::getManualPlayer(){
	return this->manualPlayer;
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