#pragma once
#include <iostream>
#include <vector>
#include "Coordinate.h"
#include "Pawn.h"
#include "King.h"
#include "Board.h"
#include "Game.h"

Game::Game() {
	turn_ = 0;
}

int Game::getTurn() const{
	return turn_;
}

const Board& Game::getBoard() const{
	return board_;
}
