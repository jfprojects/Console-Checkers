#include <iostream>
#include <string>
#include "Coordinate.h"

Coordinate::Coordinate() {	
	setCoordinate(0, 0);
}

Coordinate::Coordinate(std::string xy) {
	x_ = (int)xy[0] - '0';
	y_ = (int)xy[2] - '0';
}

Coordinate::Coordinate(int x, int y) {
	setCoordinate(x, y);
}

void Coordinate::setCoordinate(int x, int y) {
	x_ = x;
	y_ = y;
}

std::string Coordinate::getCoordinateString() const {
	return "(" + std::to_string(x_) + "," + std::to_string(y_) + ")";
}

bool Coordinate::operator==(const Coordinate& other) {
	return x_ == other.x_ && y_ == other.y_;
}

bool Coordinate::operator!=(const Coordinate& other) {
	return !(*this == other);  // Invert the result of ==, this way we only need maintain implementation of ==
}