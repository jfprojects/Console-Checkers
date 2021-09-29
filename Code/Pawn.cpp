#include <iostream>
#include <vector>
#include <cmath>
#include "Coordinate.h"
#include "Pawn.h"
#include "Board.h"

Pawn::Pawn() {
	player_ = 0;
	type_ = 'p';
}

Pawn::Pawn(int player) {
	player_ = player;
	type_ = 'p';
}

std::vector<Coordinate> Pawn::findMoves(Coordinate selection, const Board& board) {
	int x = selection.x_;
	int y = selection.y_;

	int board_size = board.getSize();
	const auto& board_array = board.getBoardArray();

	// Define the move deltas
	std::vector<int> x_deltas;
	std::vector<int> y_deltas;
	if (player_ == 0) {
		x_deltas.insert(x_deltas.end(), { 1, 1, 2, 2 });
		y_deltas.insert(y_deltas.end(), { -1, 1, -2, 2 });
	}
	else {
		x_deltas.insert(x_deltas.end(), { -1, -1, -2, -2 });
		y_deltas.insert(y_deltas.end(), { -1, 1, -2, 2 });
	}

	// Find moves
	std::vector<Coordinate> moves;
	for (unsigned i = 0; i < x_deltas.size(); i++) {
		int x_to = x + x_deltas[i];
		int y_to = y + y_deltas[i];
		Coordinate move = Coordinate(x_to, y_to);
		std::cout << player_ << selection.getCoordinateString() << " " << move.getCoordinateString() << std::endl;
		if (board.checkOnBoard(move)) {
			if (std::abs(x_deltas[i]) == 1) {
				if (!board_array[x_to][y_to]){
					moves.push_back(move);
				}
			}
			else {
				int x_mid = (x + x_to) / 2;
				int y_mid = (y + y_to) / 2;
				if (board_array[x_mid][y_mid]) {
					if (board_array[x_mid][y_mid]->getPlayer() != player_) {
						moves.push_back(move);
					}
				}
			}
		}
	}

	return moves;

}