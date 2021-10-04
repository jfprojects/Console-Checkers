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
	void removeAllPieces();

	bool checkMove(Coordinate c_from, Coordinate c_to, Board& board);
	bool executeMove(Coordinate c_from, Coordinate c_to, Board& board);
	void attemptPromotion(Board& board);

	bool checkMovePossible(int player, const Board& board);
	
	// User input functions
	std::optional<Coordinate> selectPiece() const;
	std::optional<std::vector<Coordinate>> requestMoves() const;

	bool executeMoveVector(Coordinate selection, std::vector<Coordinate> moves, int player, Board& board);

	// Special commands
	bool specialCommand(Coordinate dummy);  
	void requestDraw();
	void quit();

	void skipTurn(std::string message);
	void Turn();

	void startGame();
	void endGame(std::string message);

	void displayGameState();

private:
	int turn_;
	bool game_active_;
	std::map<int, std::string> name_map_;
	Board board_ = Board();
	Controller controller;

};