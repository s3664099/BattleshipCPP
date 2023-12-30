#include "board.h"

//Change the cells for the board from string to char
//Create the potential hits in a set
//Move into a list as pointer
//Destroy the set afterwards

Board::Board(string objectName,int size) {
	std::srand(std::time(0));

	this->gridSize = 9;
	this->objectName = objectName;
	this->rows = size;
	this->grid = std::vector<std::vector<std::string>>(size, std::vector<std::string>(size, "."));
	this->spotsHit = grid = std::vector<std::vector<std::string>>(size, std::vector<std::string>(size, "."));
	ships = new std::vector<Ship>();
	
	ships->push_back(Ship(4,'e',"Aircraft Carrier"));
	ships->push_back(Ship(4,'d',"BattleShip"));
	ships->push_back(Ship(3,'b',"Submarine"));
	ships->push_back(Ship(3,'c',"Cruiser"));
	ships->push_back(Ship(2,'a',"Destroyer"));
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

vector<Ship>* Board::getShips() {
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
		printf("%s %d %c\n",ship.getName().c_str(),ship.getLength(),ship.getLetter());
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

	placeShip(&ship,shipX,shipY,posX,posY,length,code,angle);
}

set<Coordinate> Board::selectPlaces(int left, int down, set<Coordinate> potentialPlace,int length,int angle) {

	left = this->gridSize - left;
	down = this->gridSize - down;

	//Goes across the board and checks the positions the ship will occupy to see if it is valid
	for (int x=0;x<left;x++) {
		for (int y= 0;y<down;y++) {
			bool used = false;

			for (int z=0;z<length;z++) {

				//if there is a space next to the ship, the position is not valid
				for(Coordinate spot:usedSpots) {

					//Different calculations depending on angle
					if(angle == 0) {

						//Checks if this position has already been taken
						if ((spot.getX() == x) && (spot.getY() == y+z)) {
							used = true;
						}
						
					} else if (angle == 1) {
						if ((spot.getX() == x+z) && (spot.getY() == y)) {
							used = true;
						}
					}
				}
			}

			//If the position hasn't been taken, adds it to the list
			if (!used) {
				Coordinate coord(x,y);
				potentialPlace.insert(coord);
			}
			
		}
	}
	return potentialPlace;
}

//Places the ship on the board
void Board::placeShip(Ship* ship, int shipX, int shipY, int posX, int posY, int length, char code, int angle) {

	int placeShipX = shipX;
	int placeShipY = shipY;

	//Add the ship to the board
	for (int x=0;x<length;x++) {
		this->grid[placeShipX][placeShipY] = code;
		placeShipX += posX;
		placeShipY += posY;
	}

	ship->addCoordinates(shipX,shipY,posX,posY,length);

	if (angle == 1) {
		for (int x=-1;x<2;x++) {
			for (int y=shipX-1;y<shipX+length+1;y++) {
				Coordinate coord(y,shipY+x);
				usedSpots.insert(coord);
				ship->addHitSections(y,shipY+x);
			}
		}
	} else {
		for (int x=-1;x<2;x++) {
			for (int y=shipY-1;y<shipY+length+1;y++) {
				Coordinate coord(shipX+x,y);
				usedSpots.insert(coord);
				ship->addHitSections(shipX+x,y);
			}
		}
	}
}

//Checks which ship has been destroyed
int Board::checkWhichShip(Coordinate coOrds, string playerName) {

	Ship* shipToRemove = checkShipHit(coOrds, playerName);
	int won = 1;

	if (shipToRemove != nullptr) {
		won = 2;

		//Marks off coordinates on board that was occupied by the ship
		set <Coordinate> sectionsToMark = shipToRemove->getHitSections();
  		markGrid(sectionsToMark);
		removeShip(shipToRemove);

	}

	//Checks if there are any ships left on the board
 	if (checkRemainingShips()) {
 		won = 3;
	}

	return won;
}

Ship* Board::checkShipHit(Coordinate coOrds, string playerName) {

	Ship* shipToRemove;

	for (Ship ship:*ships) {

		if(ship.checkCoordinates(coOrds.getX(),coOrds.getY(),playerName)) {
			shipToRemove = &ship;
			ship.sunkShip(playerName);
		}
	}

	return shipToRemove;
}

void Board::removeShip(Ship* shipToRemove) {
	
	int ship_no = 0;
	int ship_key = -1;

	for (Ship ship:*ships) {

		if (ship.getName() == shipToRemove->getName()) {
			ship_key = ship_no;
		}
		ship_no ++;
	}

	ships->erase(ships->begin()+ship_key);

}

bool Board::checkRemainingShips() {
	bool noShips = false;

	if (ships->size() == 0) {
		noShips = true;
	}

	return noShips;
}

//Marks the sections of the grid the ship occupies as a hit
void Board::markGrid(set<Coordinate> sectionsToMark) {

	for (Coordinate mark:sectionsToMark) {
		if ((mark.getX()>-1) && (mark.getX()<10)) {
			if ((mark.getY()>-1) && (mark.getY()<10)) {
				this->grid[mark.getX()][mark.getY()] = "0";
				this->spotsHit[mark.getX()][mark.getY()] = "0";
			}
		}
	}
}

void Board::testSinkShip(string playerName) {

	//Creates a copy of the ship set
	std::vector <Ship> copyShips = *ships;

	//Goes through each of the ships
	for (Ship ship:copyShips) {

		//Gets co-ordinates of the ships
		set<Coordinate> coords = ship.getCoordinates();
		std::cout<<coords.size()<<std::endl;

		std::cout<<std::endl;
		std::cout<<ship.getName()<<" "<<ship.getLetter()<<std::endl;

		for(Coordinate coord:coords) {
			std::cout<<coord.getX()<<" "<<coord.getY()<<std::endl;
			std::cout<<checkWhichShip(coord,playerName)<<std::endl;
		}
	}
}