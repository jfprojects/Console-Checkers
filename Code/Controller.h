#pragma once
#include <iostream>
#include <string>
#include "Game.h"

class Controller {
	public:
		template<typename T>
		T getInput();

		void displayMessage(std::string s);

		void displayGameState(const Game& game);

	private:
};
