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
	const Board& getStaticBoard() const;
	Board& getDynamicBoard ();

	// A repeat of the piece manipulation functions found in board. They are used for debugging; manipulating pieces of board_ around to debug.
	bool movePiece(Coordinate c_from, Coordinate c_to); 
	bool removePiece(Coordinate c);
	bool addPiece(Coordinate c, char piece_type, int player);

	bool checkMove(Coordinate c_from, Coordinate c_to, Board& board);
	bool executeMove(Coordinate c_from, Coordinate c_to, Board& board);
	void attemptPromotion(Board& board);

	std::optional<Coordinate> selectPiece() const;
	std::optional<std::vector<Coordinate>> requestMoves() const;

	bool executeMoveVector(Coordinate selection, std::vector<Coordinate> moves, int player, Board& board);

	void skipTurn(std::string message);
	void Turn();

	void startGame();
	
	void displayGameState();

private:
	int turn_;
	std::map<int, std::string> name_map_;
	Board board_ = Board();
	Controller controller;

};