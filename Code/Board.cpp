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
	
	Pawn* white_pawn_ptr = new Pawn(0);
	King* white_king_ptr = new King(0);
	Pawn* black_pawn_ptr = new Pawn(1);
	King* black_king_ptr = new King(1);

	// Fill in white pieces
	for (int i = 0; i < 3; i++) {
		for (int j = (i % 2 == 0) ? 0 : 1; j < size_; j += 2) {
			board_array_[i][j] = white_pawn_ptr;
		}
	}

	// Fill in black pieces
	for (int i = 5; i < size_; i++) {
		for (int j = (i % 2 == 0) ? 0 : 1; j < size_; j += 2) {
			board_array_[i][j] = black_pawn_ptr;
		}
	}
}

int Board::getSize() const {
	return size_;
}

const std::vector<std::vector<Piece*>> & Board::getBoardArray() const {
	return board_array_;
}
