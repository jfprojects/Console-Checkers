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

const Board& Game::getStaticBoard() const{
	return board_;
}

Board& Game::getDynamicBoard() {
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

void Game::removeAllPieces() {
	board_.removeAllPieces();
}

std::optional<Coordinate> Game::selectPiece() const {

	controller.displayMessage("Select piece \"x,y\": ");
	std::string input = controller.getInput<std::string>();

	// Special commands
	if (input == "quit") {
		Coordinate dummy_c = Coordinate(-10, -10);
		return dummy_c;
	}
	else if (input == "draw") {
		Coordinate dummy_c = Coordinate(-20, -20);
		return dummy_c;
	}

	// Check for valid selection
	int board_size = board_.getSize();
	const auto& board_array = board_.getBoardArray();

	if (input.length() == 3 
		&& 0 <= input[0]-'0' && input[0]-'0' <= board_size-1 
		&& input[1] == ','
		&& 0 <= input[2]-'0' && input[2]-'0' <= board_size-1) {  // Check valid string input
																 // IMPORTANT: Will need to check using regex if board_size >= 11
		Coordinate c = Coordinate(input);
		std::string selection_message = board_.checkValidSelection(c, turn_);
		controller.displayMessage(selection_message);
		if (selection_message.find("Invalid selection") != std::string::npos) {
			return {};
		}
		else {
			return c;
		}
	}
	else {
		controller.displayMessage(input + " contains invalid syntax\n");
		return {};
	}
}

std::optional<std::vector<Coordinate>> Game::requestMoves() const {
	/*
	Request user to innput sequence of corrdinates to represent moves. 
	Only checks for correct syntax.
	*/
	int board_size = board_.getSize();

	controller.displayMessage("Input moves \"x,y\" (if you want to make multiple jumps, delineate \"x,y\" with \" \"): ");
	std::string input = controller.getInput<std::string>();

	// Special commands
	if (input == "quit") {
		std::vector<Coordinate> dummy_vector = { Coordinate(-10, -10) };
		return dummy_vector;
	}
	else if (input == "draw") {
		std::vector<Coordinate> dummy_vector = { Coordinate(-20, -20) };
		return dummy_vector;
	}

	unsigned i = 0;
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
	return board.checkMove(c_from, c_to);
}

bool Game::executeMove(Coordinate c_from, Coordinate c_to, Board& board) {
	return board.executeMove(c_from, c_to);
}

void Game::attemptPromotion(Board& board){
	board.attemptPromotion();
}

bool Game::checkMovePossible(int player, const Board& board) {
	return board.checkMovePossible(player);
}

bool Game::executeMoveVector(Coordinate selection, std::vector<Coordinate> moves, int player, Board& board) {
	/*
	Coordinate selection:			coordinate of selected piece
	std::vector<Coordinate> moves:	vector of moves corresponding to coordinates
	int player:						which player's turn
	Board& board:					the board we want to apply these moves to

	return:							bool indicating if moves were able to be executed successfully

	This function requires "board" argument because it needs to be able to execute moves on copies of ".board_" to verify that the moves are valid.
	*/

	Coordinate current_selection = selection;

	for (std::size_t i = 0; i < moves.size(); i++) {
		Coordinate move = moves[i];

		if (checkMove(current_selection, move, board)) {
			bool capture_made = executeMove(current_selection, move, board);
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

bool Game::specialCommand(Coordinate c) {
	/*
	return bool: indicating if c was a special command 
	*/
	if (c == Coordinate(-10, -10)) {
		endGame(name_map_[turn_] + " has left the game");
		return true;
	}
	else if (c == Coordinate(-20, -20)) {
		requestDraw();
		return true;
	}
	else {
		return false;
	}
}

void Game::requestDraw() {
	bool draw_game = false;
	controller.displayMessage(name_map_[turn_] + " has requested a draw. ");
	while (true) {
		controller.displayMessage("Does " + name_map_[(turn_ + 1) % 2] + " accept? y / n \n");
		std::string opponent_response = controller.getInput<std::string>();
		if (opponent_response.size() > 0) {
			if (opponent_response[0] == 'y') {
				draw_game = true;
				break;
			}
			else if (opponent_response[0] == 'n') {
				draw_game = false;
				break;
			}
		}
		controller.displayMessage("Invalid input, try again. ");
	}
	if (draw_game) {
		endGame(name_map_[(turn_ + 1) % 2] + " has accepted you request to draw. The game has ended in a draw.");
	}
}

void Game::quit() {
	endGame(name_map_[turn_] + " has left the game");
}

void Game::skipTurn(std::string message) {
	turn_ = (turn_ + 1) % 2;  // increment turn
	controller.displayMessage(message);
}

void Game::Turn() {
	displayGameState();
	controller.displayMessage(name_map_[turn_] + "'s turn \n");

	// Check if player has any moves
	if (!board_.checkMovePossible(turn_)) {
		skipTurn("No possible moves, ending turn");
		return;
	}

	// Select Piece
	Coordinate selected_coordinate;
	while (true) {
		std::optional<Coordinate> c_opt = selectPiece();
		if (c_opt) {
			selected_coordinate = *c_opt;
			// Check special commands
			bool was_special_command = specialCommand(selected_coordinate);
			if (!game_active_) {
				return;
			}

			// Break out of loop if input was not a special command
			if (!was_special_command) {
				break;
			}
		}
	}
	
	// Prompt user to input moves until a valid input, then execute moves.
	while (true) {
		auto moves = requestMoves()
		if (moves) {
			// Check special commands
			bool was_special_command = specialCommand(moves->at(0));
			if (!game_active_) {
				return;
			}
			// If not special command, check if valid input
			if (!was_special_command) {
				// Create a copy of board_ and run the moves through this copy to check if the moves are valid. The board_ copy will be modified during this process, which is why we do not want to directly check on board_.
				Board temp_board = board_;
				if (executeMoveVector(selected_coordinate, *moves, turn_, temp_board)) {
					executeMoveVector(selected_coordinate, *moves, turn_, board_);
					break;
				}
			}
		}
		controller.displayMessage("Your input contains an invalid move, try again");
	}

	turn_ = (turn_ + 1) % 2; 
}
	

void Game::startGame() {
	game_active_ = true;
	while (game_active_) {
		Turn();
	}
}

void Game::endGame(std::string message) {
	controller.displayMessage(message);
	game_active_ = false;
}

void Game::displayGameState() {
	int board_size = board_.getSize();
	const auto& board_array = board_.getBoardArray();  // auto will infer std::vector<std::vector<Piece*>> but we need to specify const and &

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
	controller.displayMessage("\n");
}
