#include <iostream>
#include <vector>
#include "Coordinate.h"
#include "King.h"

King::King() {
	player_ = 0;
	type_ = 'p';
}

King::King(int player) {
	player_ = player;
	type_ = 'p';
}

std::vector<Coordinate> King::findMoves(Coordinate current_position) {
	int x = current_position.x_;
	int y = current_position.y_;

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