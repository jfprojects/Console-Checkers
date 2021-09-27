#pragma once
#include <string>

class Coordinate {
	public:

		Coordinate();  // default constructor
		Coordinate(int, int);  // two param constructor

		void setCoordinate(int, int); 
		std::string getCoordinateString();

		bool operator==(const Coordinate&);  // overload == operator
		bool operator!=(const Coordinate&);  // overload != operator
		
		int x_;
		int y_;

	private:
};
