#pragma once
#include <iostream>
#include <string>

class Controller {
	public:
		template<typename T>
		T getInput() const {
			T input;
			std::getline(std::cin, input);  // std::cin >> input does not handle spaces and causes weird output, use getline instead
			return input;
		};

		void displayMessage(std::string s) const;

	private:
};
