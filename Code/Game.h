#pragma once
#include <iostream>
#include <vector>
#include "Coordinate.h"
#include "Pawn.h"
#include "King.h"
#include "Board.h"
#include <map>

class Game {
public:
	Game();

	int getTurn() const;
	const std::map<int, std::string>& getNameMap() const;
	const Board& getBoard() const;


private:
	int turn_;
	std::map<int, std::string> name_map_;
	Board board_;


};