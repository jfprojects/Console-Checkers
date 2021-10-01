#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "Coordinate.h"
#include "Pawn.h"
#include "King.h"
#include "Board.h"
#include "Controller.h"

Board::Board() {
	size_ = 8;
	for (int i = 0; i < size_; i++) {
		board_array_.push_back(std::vector<Piece*>(size_, nullptr));
	}

	// Fill in white pieces
	for (int i = 0; i < 3; i++) {
		for (int j = (i % 2 == 0) ? 0 : 1; j < size_; j += 2) {
			board_array_[i][j] = new Pawn(0);
		}
	}

	// Fill in black pieces
	for (int i = 5; i < size_; i++) {
		for (int j = (i % 2 == 0) ? 0 : 1; j < size_; j += 2) {
			board_array_[i][j] = new Pawn(1);
		}
	}
}

Board::Board(const Board& b) {
	const auto& board_array = b.getBoardArray();
	size_ = b.getSize();

	for (int i = 0; i < size_; i++) {
		board_array_.push_back(std::vector<Piece*>(size_, nullptr));
	}

	for (int i = 0; i < size_; i++) {
		for (int j = 0; j < size_; j++) {
			if (board_array[i][j]) {
				switch (board_array[i][j]->getType()) {
				case 'p':
					board_array_[i][j] = new Pawn(board_array[i][j]->getPlayer());
					break;
				case 'k':
					board_array_[i][j] = new King(board_array[i][j]->getPlayer());
					break;
				}
			}
		}
	}
}

int Board::getSize() const {
	return size_;
}

const std::vector<std::vector<Piece*>> & Board::getBoardArray() const {
	return board_array_;
}

bool Board::checkOnBoard(Coordinate c) const {
	int x = c.x_;
	int y = c.y_;

	if (x < 0 || x >= size_ || y < 0 || y >= size_) {
		return false;
	}
	
	return true;
}

bool Board::checkValidSelection(Coordinate c, int player) const {
	if (!checkOnBoard(c)) {
		return false;
	}

	if (board_array_[c.x_][c.y_]) {  // Check if empty space
		if (board_array_[c.x_][c.y_]->getPlayer() == player) {  // Check if piece belongs to player
			controller.displayMessage("You have selected: " + std::string(1, board_array_[c.x_][c.y_]->getType()) + "  " + c.getCoordinateString() + '\n');  // char_arr + char + char_arr is NOT ALLOWED																																	// char_arr + char WILL GIVE NONSENSE
			return true;
		}
		else {
			controller.displayMessage(c.getCoordinateString() + " belongs to other player\n");
			return false;
		}
	}
	else {
		controller.displayMessage(c.getCoordinateString() + " is an empty space\n");
		return false;
	}
}

bool Board::movePiece(Coordinate c_from, Coordinate c_to) {
	if (!checkOnBoard(c_from)) {
		controller.displayMessage(c_from.getCoordinateString() + "is not on the board");
		return false;
	}

	if (!checkOnBoard(c_to)) {
		controller.displayMessage(c_to.getCoordinateString() + "is not on the board");
		return false;
	}

	if (board_array_[c_from.x_][c_from.y_]) {
		if (board_array_[c_to.x_][c_to.y_]) {
			controller.displayMessage("There is already a pice at: " + c_to.getCoordinateString());
			return false;
		}
		else {
			board_array_[c_to.x_][c_to.y_] = board_array_[c_from.x_][c_from.y_];
			board_array_[c_from.x_][c_from.y_] = nullptr;
			return true;
		}
	}
	else {
		controller.displayMessage("There is no piece at: " + c_from.getCoordinateString());
		return false;
	}
}

bool Board::removePiece(Coordinate c) {
	if (board_array_[c.x_][c.y_]) {
		delete board_array_[c.x_][c.y_];
		board_array_[c.x_][c.y_] = nullptr;
		return true;
	}
	else {
		return false;
	}
}

bool Board::addPiece(Coordinate c, char piece_type, int player) {
	if (board_array_[c.x_][c.y_]) {
		return false;
	}
	else {
		if (piece_type == 'p') {
			board_array_[c.x_][c.y_] = new Pawn(player);
			return true;
		}
		else if (piece_type == 'k') {
			board_array_[c.x_][c.y_] = new King(player);
			return true;
		}
		else {
			return false;
		}
	}
}

bool Board::checkMove(Coordinate c_from, Coordinate c_to) {
	std::vector<Coordinate> possible_moves = board_array_[c_from.x_][c_from.y_]->findMoves(c_from, *this);
	if (std::find(possible_moves.begin(), possible_moves.end(), c_to) != possible_moves.end()) {
		return true;
	}
	return false;
}

bool Board::executeMove(Coordinate c_from, Coordinate c_to) {
	/*
	THIS FUNCTION SHOULD ONLY BE CALLED FOR VALID MOVES. CHECK IF MOVE IS VALID WITH .checkMove() BEFORE CALLINNG
	Moves piece from c_from to c_to and will perform capture on board.
	return: bool indicating if capture was made
	*/
	movePiece(c_from, c_to);
	if (std::abs(c_to.x_ - c_from.x_) == 2) {
		Coordinate c_mid = Coordinate((c_to.x_ + c_from.x_) / 2, (c_to.y_ + c_from.y_) / 2);
		removePiece(c_mid);
		return true;
	}
	return false;
}

void Board::attemptPromotion() {
	/*
	 Checks board to see if there are any possible promotions and performs promotions if available
	 */

	// Player 1 promotion
	for (int j = 0; j < size_; j++) {
		if (board_array_[0][j]) {
			if (board_array_[0][j]->getPlayer() == 1 && board_array_[0][j]->getType() == 'p') {
				removePiece(Coordinate(0, j));
				addPiece(Coordinate(0, j), 'k', 1);
			}
		}
	}

	// Player 0 promotion
	for (int j = 0; j < size_; j++) {
		if (board_array_[size_ - 1][j]) {
			if (board_array_[size_ - 1][j]->getPlayer() == 0 && board_array_[size_ - 1][j]->getType() == 'p') {
				removePiece(Coordinate(size_ - 1, j));
				addPiece(Coordinate(size_ - 1, j), 'k', 0);
			}
		}
	}
}

void Board::displayBoardArray() const {

	for (int i = 0; i < size_; i++) {
		for (int j = 0; j < size_; j++) {
			if (board_array_[i][j]) {
				std::string piece_type(1, board_array_[i][j]->getType());
				std::string player = std::to_string(board_array_[i][j]->getPlayer());
				controller.displayMessage(piece_type + player);
			}
			else {
				controller.displayMessage("  ");
			}
		}
		controller.displayMessage("\n");
	}
	controller.displayMessage("\n\n");
}
