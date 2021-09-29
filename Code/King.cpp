#include <iostream>
#include <vector>
#include "Coordinate.h"
#include "King.h"
#include "Board.h"

King::King() {
	player_ = 0;
	type_ = 'k';
}

King::King(int player) {
	player_ = player;
	type_ = 'k';
}

std::vector<Coordinate> King::findMoves(Coordinate selection, const Board& board) {
	int x = selection.x_;
	int y = selection.y_;

	// Define the move deltas
	std::vector<int> x_deltas;
	std::vector<int> y_deltas;
	if (player_ == 0) {
		x_deltas.insert(x_deltas.end(), { -1, 1, -2, 2, -1, 1, -2, 2 });
		y_deltas.insert(y_deltas.end(), { 1, 1, 2, 2, -1, -1, -2, -2 });
	}
	else {
		x_deltas.insert(x_deltas.end(), { -1, 1, -2, 2 });
		y_deltas.insert(y_deltas.end(), { -1, -1, -2, -2 });
	}

	// Find moves
	std::vector<Coordinate> moves;
	for (unsigned i = 0; i < x_deltas.size(); i++) {
		Coordinate move = Coordinate(x + x_deltas[i], y + y_deltas[i]);
		moves.push_back(move);
	}

	return moves;

}