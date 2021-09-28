#pragma once
#include <iostream>
#include <string>
#include "Controller.h"

template<typename T>
T Controller::getInput() {
	T input;
	std::cin >> input;
	return input;
}

void Controller::displayMessage(std::string s) {
	std::cout << s;
}

//void Controller::displayGameState(const Game& game) {
//	const Board& B = game.getBoard();
//	int size = B.getSize();
//	const auto& board_array = B.getBoardArray();  // auto will infer std::vector<std::vector<Piece*>> but we need to specify const and &
//	
//	std::cout << game.getNameMap().at(0) << "'s turn" << std::endl;  // map [] opertor is not available for const map, must use .at operaator
//
//	for (int i = 0; i < size; i++) {
//		for (int j = 0; j < size; j++) {
//			if (board_array[i][j]) {
//				std::cout << board_array[i][j]->getType() << board_array[i][j]->getPlayer() << " ";
//			}
//			else {
//				std::cout << "   ";
//			}
//		}
//		std::cout << std::endl;
//	}
//}


