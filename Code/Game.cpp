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
