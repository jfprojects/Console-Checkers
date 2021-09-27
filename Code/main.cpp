#include <iostream>
#include "Coordinate.h"
#include "Pawn.h"
#include "King.h"
#include "Board.h"

int main() {
	Coordinate c1 = Coordinate();
	c1.setCoordinate(10, 20);
	Coordinate c2 = Coordinate(1,2);

	std::cout << "c1: ";
	c1.displayCoordinate();
	std::cout << std::endl;

	std::cout << "c2: ";
	c2.displayCoordinate();
	std::cout << std::endl;

	std::cout << "c1 == c2: " << (c1 == c2) << std::endl;
	std::cout << std::endl;

	Pawn p = Pawn();
	std::cout << "Pawn moves: " << std::endl;
	std::vector<Coordinate> p_moves = p.findMoves(Coordinate(4, 4));
	for (Coordinate c : p_moves) {
		c.displayCoordinate();
	}
	std::cout << std::endl;

	King k = King();
	std::cout << "King moves: " << std::endl;
	std::vector<Coordinate> k_moves = k.findMoves(Coordinate(4, 4));
	for (Coordinate c : k_moves) {
		c.displayCoordinate();
	}
	std::cout << std::endl;

	Board board = Board();
	board.displayBoard();
}