#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <optional>
#include <algorithm>

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
		if (board_.checkValidSelection(c, turn_)) {
			controller.displayMessage("You have selected: " + c.getCoordinateString());
			return c;
		}
		else {
			return {};
		}
	}
	else {
		controller.displayMessage(input + " contains invalid syntax\n");
		return {};
	}
}

std::optional<std::vector<Coordinate>> Game::requestMoves() const {
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

bool Game::checkMove(Coordinate c_from, Coordinate c_to, Board& board) {
	std::vector<Coordinate> possible_moves = board.getBoardArray()[c_from.x_][c_from.y_]->findMoves(c_from, board);
	if (std::find(possible_moves.begin(), possible_moves.end(), c_to) != possible_moves.end()) {
		return true;
	}
	return false;
}

bool Game::executeMove(Coordinate c_from, Coordinate c_to, Board& board) {
	/*
	Moves piece from c_from to c_to and will perform capture on board.
	return: bool indicating if capture was made
	*/
	board.movePiece(c_from, c_to);
	if (std::abs(c_to.x_ - c_from.x_) == 2) {
		Coordinate c_mid = Coordinate((c_to.x_ + c_from.x_) / 2, (c_to.y_ + c_from.y_) / 2);
		board.removePiece(c_mid);
		return true;
	}
	return false;
}

bool Game::executeMoveVector(Coordinate selection, std::vector<Coordinate> moves, int player, Board& board) {
	Coordinate current_selection = selection;

	for (std::size_t i=0; i < moves.size(); i++) {
		Coordinate move = moves[i];

		if (checkMove(current_selection, move, board)) {
			bool capture_made = executeMove(current_selection, move, board);
			std::cout << "made capture?: " << capture_made << std::endl;
			attemptPromotion(board);
			if (capture_made) {
				current_selection = move;
			}
			else {  // if no capture, subsequent moves are not allowed
				if (i != moves.size() - 1) {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	return true;
}

void Game::attemptPromotion(Board& board){
	/*
	 Checks board to see if there are any possible promotions and performs promotions if available
	 */

	const auto& board_array = board.getBoardArray();
	int board_size = board.getSize();

	// Player 1 promotion
	for (int j = 0; j < board_size; j++) {
		if (board_array[0][j]) {
			if (board_array[0][j]->getPlayer() == 1 && board_array[0][j]->getType() == 'p') {
				board.removePiece(Coordinate(0, j));
				board.addPiece(Coordinate(0, j), 'k', 1);
			}
		}
	}

	// Player 0 promotion
	bool player0_promoted = false;
	for (int j = 0; j < board_size; j++) {
		if (board_array[board_size-1][j]) {
			if (board_array[board_size - 1][j]->getPlayer() == 0 && board_array[board_size - 1][j]->getType() == 'p') {
				board.removePiece(Coordinate(board_size - 1, j));
				board.addPiece(Coordinate(board_size - 1, j), 'k', 0);
			}
		}
	}
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
	
	while (true) {
		auto moves = requestMoves();
		if (moves) {
			Board temp_board = board_;  // Call copy constructor, temp_board will be modified to verify moves are valid

		}
		else {
			controller.displayMessage("Try again");
			continue;
		}
	}

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

	std::string top_axis = "   ";
	for (int j = 0; j < board_.getSize(); j++) {
		top_axis = top_axis + std::to_string(j) + " ";
	}
	controller.displayMessage(top_axis + "\n");

	for (int i = 0; i < board_.getSize(); i++) {
		controller.displayMessage(std::to_string(i) + " ");
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
