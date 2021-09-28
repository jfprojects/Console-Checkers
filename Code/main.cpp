#include <iostream>
#include "Coordinate.h"
#include "Pawn.h"
#include "King.h"
#include "Board.h"
#include "Game.h"
#include "Controller.h"

int main() {
	
	Pawn p = Pawn();
	std::cout << "Pawn moves: " << std::endl;
	std::vector<Coordinate> p_moves = p.findMoves(Coordinate(4, 4));
	for (Coordinate c : p_moves) {
		std::cout << c.getCoordinateString();
	}
	std::cout << std::endl;

	King k = King();
	std::cout << "King moves: " << std::endl;
	std::vector<Coordinate> k_moves = k.findMoves(Coordinate(4, 4));
	for (Coordinate c : k_moves) {
		std:: cout << c.getCoordinateString();
	}
	std::cout << std::endl;

	Board board = Board();

	board.movePiece(Coordinate(2, 0), Coordinate(3, 1));

	board.removePiece(Coordinate(3, 1));

	Game game = Game();

	game.displayGameState();

	game.movePiece(Coordinate(2, 0), Coordinate(3, 1));

	game.displayGameState();

	game.removePiece(Coordinate(3, 1));

	game.displayGameState();
	
}