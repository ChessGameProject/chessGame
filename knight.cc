#include "knight.h"
#include "piece.h"

// Create a piece with name 'n'
Knight::Knight(int player) : Piece(player, 'n') {}

// Checks if a given move is valid
bool isMoveValid(int endX, int endY) const {
	if !( (std::abs(endX - x) == 2 &&
				std::abs(endY - y) == 3) ||
				(std::abs(endX - x) == 3 &&
				std::abs(endY - y) == 2) ) {
		return false;
		// Moves must be L-shaped
	}

	// Check that the King is not going to be in check
  // game.inCheck(int player);
  return true;
}
