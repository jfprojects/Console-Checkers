#pragma once
#include <vector>
#include "Coordinate.h"
#include "Piece.h"

class Pawn : public Piece {
	public:
		//using Piece::Piece;  // inherit ALL base class constructors
		//					   // If you want only some, need to define the constructors manually
		Pawn();
		Pawn(int player);

		std::vector<Coordinate> findMoves(Coordinate c);
};
