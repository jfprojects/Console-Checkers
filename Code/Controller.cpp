#pragma once
#include <iostream>
#include <string>
#include "Controller.h"
#include "Game.h"

template<typename T>
T Controller::getInput() {
	T input;
	std::cin >> input;
	return input;
}

void Controller::displayMessage(std::string s) {
	std::cout << s << std::endl;
}

void Controller::displayGameState(Game game) {
	const Board& B = game.getBoard();
	int size = B.getSize();
	auto board_array = B.getBoardArray();  // auto will infer const std::vector<std::vector<Piece*>>&
	
	// Add code to display player turn

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board_array[i][j]) {
				std::cout << board_array[i][j]->getType() << board_array[i][j]->getPlayer() << " ";
			}
			else {
				std::cout << "   ";
			}
		}
		std::cout << std::endl;
	}
}


