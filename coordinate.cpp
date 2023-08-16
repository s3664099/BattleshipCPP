#include "coordinate.h"

Coordinate::Coordinate() : x(0), y(0) {}

Coordinate::Coordinate(int xVal, int yVal) : x(xVal), y(yVal) {}

int Coordinate::getX() {
	return this->x;
}

int Coordinate::getY() {
	return this->y;
}