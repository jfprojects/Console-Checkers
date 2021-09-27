#pragma once
#include <vector>
#include "Coordinate.h"
#include "Piece.h"

class King : public Piece {
public:
	//using Piece::Piece;  // inherit ALL base class constructors
	//				  	   // If you want only some, need to define the constructors manually
	King();
	King(int player);

	std::vector<Coordinate> findMoves(Coordinate c);
};
