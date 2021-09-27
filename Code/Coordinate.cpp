#include <iostream>
#include "Coordinate.h"

Coordinate::Coordinate() {	
	setCoordinate(0, 0);
}

Coordinate::Coordinate(int x, int y) {
	setCoordinate(x, y);
}


void Coordinate::setCoordinate(int x, int y) {
	x_ = x;
	y_ = y;
}

void Coordinate::displayCoordinate() {
	std::cout << "(" << x_ << "," << y_ << ")" << std::endl;
}

bool Coordinate::operator==(const Coordinate& other) {
	return x_ == other.x_ && y_ == other.y_;
}

bool Coordinate::operator!=(const Coordinate& other) {
	return !(*this == other);  // Invert the result of ==, this way we only need maintain implementation of ==
}