#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Coordinate.h"
#include "Pawn.h"
#include "King.h"
#include "Board.h"
#include "Game.h"

Game::Game() {
	turn_ = 0;
	name_map_[0] = "Player 0";
	name_map_[1] = "Player 1";
}

int Game::getTurn() const {
	return turn_;
}

const std::map<int, std::string>& Game::getNameMap() const{
	return name_map_;
}

const Board& Game::getBoard() const{
	return board_;
}

bool Game::movePiece(Coordinate c_from, Coordinate c_to) {
	return board_.movePiece(c_from, c_to);
}

bool Game::removePiece(Coordinate c) {
	return board_.removePiece(c);
}

void Game::startGame() {

}

void Game::displayGameState() {
	int board_size = board_.getSize();
	const auto& board_array = board_.getBoardArray();  // auto will infer std::vector<std::vector<Piece*>> but we need to specify const and &
	
	controller.displayMessage(name_map_[0] + "'s turn \n\n");

	for (int i = 0; i < board_.getSize(); i++) {
		for (int j = 0; j < board_.getSize(); j++) {
			if (board_array[i][j]) {
				std::string piece_type(1, board_array[i][j]->getType());
				std::string player = std::to_string(board_array[i][j]->getPlayer());
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
