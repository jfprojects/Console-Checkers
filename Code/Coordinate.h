#pragma once
#include <string>

class Coordinate {
	public:
		// NOTE: (-10, -10) is reserved to denote skip turn 
		Coordinate();  // default constructor
		Coordinate(std::string);  // single string param constructor
		Coordinate(int, int);  // two param constructor

		void setCoordinate(int, int); 
		std::string getCoordinateString() const;

		bool operator==(const Coordinate&);  // overload == operator
		bool operator!=(const Coordinate&);  // overload != operator
		
		int x_;
		int y_;

	private:
};
