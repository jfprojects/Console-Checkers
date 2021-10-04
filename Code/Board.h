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
		std::string checkValidSelection(Coordinate c, int player) const;

		// These are basic piece movement/manipulations functions that do not involve game logic
		bool movePiece(Coordinate c_from, Coordinate c_to);
		bool removePiece(Coordinate c);
		bool addPiece(Coordinate c, char piece_type, int player);
		void removeAllPieces();

		// These are realistic movement/manipulations that account for game logic
		bool checkMove(Coordinate c_from, Coordinate c_to);
		bool executeMove(Coordinate c_from, Coordinate c_to);
		void attemptPromotion();

		// Check if a player has any possible moves
		bool checkMovePossible(int player) const;

		void displayBoardArray() const;

	private:
		int size_;
		std::vector<std::vector<Piece*>> board_array_;
		Controller controller;
};
