#pragma once
#include <iostream>
#include <string>

class Controller {
	public:
		template<typename T>
		T getInput() const {
			T input;
			std::cin >> input;
			return input;
		};

		void displayMessage(std::string s) const;

	private:
};
