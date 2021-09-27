#pragma once

class Coordinate {
	public:

		Coordinate();  // default constructor
		Coordinate(int, int);  // two param constructor

		void displayCoordinate();
		void setCoordinate(int, int); 

		bool operator==(const Coordinate&);  // overload == operator
		bool operator!=(const Coordinate&);  // overload != operator
		
		int x_;
		int y_;

	private:
};
