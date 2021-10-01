#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <optional>

#include "Coordinate.h"
#include "Pawn.h"
#include "King.h"
#include "Board.h"
#include "Controller.h"

class Game {
public:
	Game();

	int getTurn() const;
	const std::map<int, std::string>& getNameMap() const;
	const Board& getBoard() const;

	bool movePiece(Coordinate c_from, Coordinate c_to); 
	bool removePiece(Coordinate c);
	bool addPiece(Coordinate c, char piece_type, int player);

	std::optional<Coordinate> selectPiece() const;  // Move to private once Turn function implemented
	std::optional<std::vector<Coordinate>> requestMoves() const;

	bool checkMove(Coordinate c_from, Coordinate c_to, Board& board);
	bool executeMove(Coordinate c_from, Coordinate c_to, Board& board);
	void attemptPromotion(Board& board);

	bool executeMoveVector(Coordinate selection, std::vector<Coordinate> moves, int player, Board& board);

	void Turn();

	void startGame();
	
	void displayGameState();

private:
	int turn_;
	std::map<int, std::string> name_map_;
	Board board_ = Board();
	Controller controller;

};