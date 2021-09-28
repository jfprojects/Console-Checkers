#pragma once
#include <iostream>
#include <string>

class Controller {
	public:
		template<typename T>
		T getInput();

		void displayMessage(std::string s);

	private:
};
