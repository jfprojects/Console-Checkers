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

bool Board::movePiece(Coordinate c_from, Coordinate c_to) {

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