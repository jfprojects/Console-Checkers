#pragma once
#include <vector>
#include "Coordinate.h"
#include "Pawn.h"
#include "King.h"

class Board {
	public:
		Board();

		int getSize() const;
		const std::vector<std::vector<Piece*>> & getBoardArray() const;

	private:
		int size_;
		std::vector<std::vector<Piece*>> board_array_;

};
