#pragma once
#include <vector>
#include "Coordinate.h"

class Piece {
	public:
		int getPlayer() const;
		char getType() const;

		virtual std::vector<Coordinate> findMoves(Coordinate c) = 0;

	protected:
		int player_;  // 0 for black, 1 for white
		char type_;
};
