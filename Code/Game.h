#pragma once
#include <iostream>
#include <vector>
#include "Coordinate.h"
#include "Pawn.h"
#include "King.h"
#include "Board.h"

class Game {
public:
	Game();

	int getTurn() const;
	const Board& getBoard() const;

private:
	int turn_;
	Board board_;

};