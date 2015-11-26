#include "queen.h"
#include "piece.h"

// Create a piece with name 'q'
Queen::Queen(int player) : Piece(player, 'q') {}

// Checks if a given move is valid
bool isMoveValid(int endX, int endY) const {
	if !( endX - x == 0 ||
				endY - y == 0 ||
				endX - x == endY - y ) {
		// Moves must be square or diagonal
	}

	// Check that the King is not going to be in check
  // game.inCheck(int player);
  return true;
}
