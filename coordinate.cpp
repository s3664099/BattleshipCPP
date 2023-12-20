#include "coordinate.h"

Coordinate::Coordinate() : x(0), y(0) {}

Coordinate::Coordinate(int xVal, int yVal) : x(xVal), y(yVal) {}

int Coordinate::getX() {
	return this->x;
}

int Coordinate::getY() {
	return this->y;
}

// Define comparison operators for set ordering
bool Coordinate::operator<(const Coordinate& other) const {

    if (x != other.x) {
        return x < other.x;
    }
    return y < other.y;
}

bool Coordinate::operator==(const Coordinate& other) const {

    bool equal = false;

    if ((x == other.x) && (y == other.y))
        equal = true;

    return equal;
}