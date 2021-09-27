#pragma once
#include <iostream>
#include <vector>
#include "Coordinate.h"
#include "Pawn.h"
#include "King.h"
#include "Board.h"

Board::Board() {
	size_ = 8;
	for (int i = 0; i < size_; i++) {
		board_array_.push_back(std::vector<Piece*>(size_, nullptr));
	}
	//board_array_.push_back(std::vector<std::vector<Piece*>>(size_, std::vector<Piece*>(size_, nullptr)));
	//board_array_ = std::vector<std::vector<Piece*>>(size_, std::vector<Piece*>(size_, nullptr));  // 8x8 2d matrix of nullptr
	

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

int Board::getSize() const {
	return size_;
}

const std::vector<std::vector<Piece*>> & Board::getBoardArray() const {
	return board_array_;
}

void Board::movePiece() {

}

std::vector<Coordinate> Board::findMoves(Coordinate c) const {
	std::vector<Coordinate> valid_moves;
	if (board_array_[c.x_][c.y_]) {

	}
	else {
		return valid_moves;
	}
}