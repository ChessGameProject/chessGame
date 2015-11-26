#include "bishop.h"
#include "piece.h"

// Create a piece with name 'b'
Bishop::Bishop(int player) : Piece(player, 'b') {}

// Checks if a given move is valid
bool isMoveValid(int endX, int endY) const {
	if !( endX - x == endY - y ) {
		// Moves must be diagonal
		return false;
	}

	// Check that the King is not going to be in check
  // game.inCheck(int player);
  return true;
}
