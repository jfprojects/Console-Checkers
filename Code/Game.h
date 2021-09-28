#pragma once
#include <iostream>
#include <vector>
#include <map>
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

	void startGame();
	
	void displayGameState();

private:
	int turn_;
	std::map<int, std::string> name_map_;
	Board board_ = Board();
	Controller controller;
};