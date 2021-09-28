#include <iostream>
#include <vector>
#include <map>
#include <optional>

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

	/*game.movePiece(Coordinate(2, 0), Coordinate(3, 1));
	game.displayGameState();

	game.removePiece(Coordinate(3, 1));
	game.displayGameState();

	game.removePiece(Coordinate(0, 0));
	game.addPiece(Coordinate(0, 0), 'p', 1);
	game.displayGameState();
	
	int player_promotion = game.checkPromotion();
	game.displayGameState();

	game.removePiece(Coordinate(7, 1));
	game.addPiece(Coordinate(7, 1), 'p', 0);
	game.displayGameState();

	int player_promotion_ = game.checkPromotion();
	game.displayGameState();*/

	std::optional<std::vector<Coordinate>> c_vec_opt = game.getMoves();
	while (true) {
		if (c_vec_opt) {
			break;
		}
		c_vec_opt = game.getMoves();
	}
	std::vector<Coordinate> moves = *c_vec_opt;
	
	for (int i = 0; i < moves.size(); i++) {
		std::cout << moves[i].getCoordinateString() << std::endl;
	}
}