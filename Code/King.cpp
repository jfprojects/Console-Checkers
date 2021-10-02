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

	int board_size = board.getSize();
	const auto& board_array = board.getBoardArray();

	// Define the move deltas
	std::vector<int> x_deltas;
	std::vector<int> y_deltas;

	x_deltas.insert(x_deltas.end(), { 1, 1, 2, 2, -1, -1, -2, -2 });
	y_deltas.insert(y_deltas.end(), { 1, -1, 2, -2, 1, -1, 2, -2 });

	// Find moves
	std::vector<Coordinate> moves;
	for (unsigned i = 0; i < x_deltas.size(); i++) {
		int x_to = x + x_deltas[i];
		int y_to = y + y_deltas[i];
		Coordinate move = Coordinate(x_to, y_to);
		if (board.checkOnBoard(move)) {
			if (std::abs(x_deltas[i]) == 1) {
				if (!board_array[x_to][y_to]) {
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