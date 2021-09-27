#pragma once

class Coordinate {
	public:

		Coordinate();  // default constructor
		Coordinate(int, int);  // two param constructor

		int getX();
		int getY();
		void displayCoordinate();
		void setCoordinate(int, int); 

		bool operator==(const Coordinate&);  // overload == operator
		bool operator!=(const Coordinate&);  // overload != operator
		
	private:
		int x_;
		int y_;
};
