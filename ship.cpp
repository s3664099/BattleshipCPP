#include "ship.h"

Ship::Ship(int length, char letter, string name) {
	this->length = length;
	this->letter = letter;
	this->name = name;
	this->sunk = false;
	this->coordinates = new set<Coordinate>(); 
	this->hitSections = new set<Coordinate>(); 
}

int Ship::getLength() {
	return this->length;
}

string Ship::getName() const{
	return this->name;
}

char Ship::getLetter() {
	return this->letter;
}

bool Ship::getSunk() {
	return this->sunk;
}

//adds the coordinates that the shop will occupy on the map
void Ship::addCoordinates(int xCoord, int yCoord, int incX, int incY, int length) {

	for (int x=0;x<length;x++) {

		Coordinate coord(xCoord,yCoord);
		this->coordinates->insert(coord);
		xCoord += incX;
		yCoord += incY;
	}
}

//Adds a coordinate where the ship has been hit
void Ship::addHitSections(int xCoord,int yCoord) {
	Coordinate coord(xCoord,yCoord);
	this->hitSections->insert(coord);
}

set<Coordinate>* Ship::getHitSections() {

	return this->hitSections;
}

//Checks if the coordinates are where the ship is located
bool Ship::checkCoordinates(int xCoord,int yCoord, string playerName) {

	bool sunk = false;
	bool found = false;
	int coord_cout = 0;
	int coord_index = -1;

	//Goes through the coordinates
	for (Coordinate coord:*coordinates) {

		//If they are equal to the coordinates, marked as found
		if (coord.getX() == xCoord && coord.getY() == yCoord) {
			coord_index = coord_cout;
			found = true;
		}
		coord_cout ++;
	}

	//If found, announces that the ship has been hit
	//Also removes the coordinates from the set
	if (found) {

	    auto it = this->coordinates->begin();
	    std::advance(it, coord_index);
	    this->coordinates->erase(it);		
		cout << playerName << " hit the "<< this->name << "\n";
	}

	//Checks the size of the coordinate set. If 0 then the ship is sunk.
	if (this->coordinates->size() == 0) {
		sunk = true;
	}

	return sunk;
}

//Sets the ship and sunk, and announces it.
void Ship::sunkShip(string playerName) {
	this->sunk = true;
	cout << playerName << " sunk the "<<this->name << "\n";
}

set<Coordinate>* Ship::getCoordinates() {
	return this->coordinates;
}

// Define the less-than operator
bool Ship::operator<(const Ship& other) const {

    if (length != other.length) {
        return length < other.length;
    }
    return letter < other.letter;
}





