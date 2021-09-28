#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <optional>

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

bool Game::addPiece(Coordinate c, char piece_type, int player) {
	return board_.addPiece(c, piece_type, player);
}

std::optional<Coordinate> Game::selectPiece() const {
	controller.displayMessage("Select piece \"x,y\": ");
	std::string input = controller.getInput<std::string>();
	int board_size = board_.getSize();
	const auto& board_array = board_.getBoardArray();

	if (input.length() == 3 
		&& 0 <= input[0]-'0' && input[0]-'0' <= board_size-1 
		&& input[1] == ','
		&& 0 <= input[2]-'0' && input[2]-'0' <= board_size-1) {  // Check valid string input
																 // IMPORTANT: Will need to check using regex if board_size >= 11
		Coordinate c = Coordinate(input);
		if (board_array[c.x_][c.y_]) {  // Check if empty space
			if (board_array[c.x_][c.y_]->getPlayer() == turn_) {  // Check if piece belongs to player
				controller.displayMessage("You have selected: " + std::string(1, board_array[c.x_][c.y_]->getType()) + "  " + c.getCoordinateString() + '\n');  // char_arr + char + char_arr is NOT ALLOWED
																																								// char_arr + char WILL GIVE NONSENSE
				return c;
			}
			else {
				controller.displayMessage(input + " belongs to other player\n");
				return {};
			}
		}
		else {
			controller.displayMessage(input + " is an empty space\n");
			return {};
		}
	}
	else {
		controller.displayMessage(input + " contains invalid syntax\n");
		return {};
	}

	controller.displayMessage("You have selected");
}

std::optional<std::vector<Coordinate>> Game::getMoves() const {
	int board_size = board_.getSize();

	controller.displayMessage("Input moves \"x,y\" (if you want to make multiple jumps, delineate \"x,y\" with \" \"): ");
	std::string input = controller.getInput<std::string>();
	int i = 0;
	std::vector<Coordinate> moves;
	while (i < input.length()) {

		if (0 <= input[i] - '0' && input[i] - '0' <= board_size - 1
			&& input[i + 1] == ','
			&& 0 <= input[i+2] - '0' && input[i+2] - '0' <= board_size - 1) { // IMPORTANT: Will need to check using regex if board_size >= 11

			moves.push_back(Coordinate(input.substr(i, 3)));
		}
		else {
			controller.displayMessage(input + " contains invalid syntax\n");
			return {};
		}
		i += 4;
	}
	return moves;
}

int Game::checkPromotion(){
	/*
	 Checks board to see if there are any possible promotions

	 @return: -1 no promotions, 0 promotion for playr 0, 1 promotion for player 1
	 */
	const auto& board_array = board_.getBoardArray();
	int board_size = board_.getSize();

	// Player 1 promotion
	bool player1_promoted = false;
	for (int j = 0; j < board_size; j++) {
		if (board_array[0][j]) {
			if (board_array[0][j]->getPlayer() == 1 && board_array[0][j]->getType() == 'p') {
				board_.removePiece(Coordinate(0, j));
				board_.addPiece(Coordinate(0, j), 'k', 1);
				player1_promoted = true;
			}
		}
	}
	if (player1_promoted) {
		return 1;
	}

	// Player 0 promotion
	bool player0_promoted = false;
	for (int j = 0; j < board_size; j++) {
		if (board_array[board_size-1][j]) {
			if (board_array[board_size - 1][j]->getPlayer() == 0 && board_array[board_size - 1][j]->getType() == 'p') {
				board_.removePiece(Coordinate(board_size - 1, j));
				board_.addPiece(Coordinate(board_size - 1, j), 'k', 0);
				player0_promoted = true;
			}
		}
	}
	if (player0_promoted) {
		return 0;
	}

	return -1;
}

void Game::Turn() {
	// Select Piece
	std::optional<Coordinate> c_opt = selectPiece();
	while (true) {
		if (c_opt) {
			break;
		}
		c_opt = selectPiece();
	}
	Coordinate selected_coordinate = *c_opt;
	Piece* selected_piece = board_.getBoardArray()[selected_coordinate.x_][selected_coordinate.y_];

	//// Request moves
	//while (true) {
	//	controller.displayMessage("Input moves \"x,y\" (if you want to make multiple jumps, delineate \"x,y\" with \" \"): ");
	//	std::string moves_input = controller.getInput<std::string>();

	//	int i = 0;
	//	while (i < moves_input.length()) {
	//		if (i % 4 == 0) {}
	//	}
	//}
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
