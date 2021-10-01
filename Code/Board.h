#pragma once
#include <vector>
#include "Coordinate.h"
#include "Pawn.h"
#include "King.h"
#include "Controller.h"

class Board {
	public:
		Board();
		Board(const Board& b);
		int getSize() const;
		const std::vector<std::vector<Piece*>> & getBoardArray() const;
		
		bool checkOnBoard(Coordinate c) const;
		bool checkValidSelection(Coordinate c, int player) const;

		bool movePiece(Coordinate c_from, Coordinate c_to);  // Moves piece from c_from to c_to, does not handle captures if the move will cause capture
		bool removePiece(Coordinate c);  // Removes piece from board
		bool addPiece(Coordinate c, char piece_type, int player);

		void displayBoardArray() const;

	private:
		int size_;
		std::vector<std::vector<Piece*>> board_array_;
		Controller controller;
};
