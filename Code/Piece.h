#pragma once
#include <vector>
#include "Coordinate.h"

class Board;

class Piece {
	public:
		int getPlayer() const;
		char getType() const;

		virtual std::vector<Coordinate> findMoves(Coordinate selection, const Board& board) = 0;

	protected:
		int player_=0;  // 0 for black, 1 for white
		char type_='p';
};
