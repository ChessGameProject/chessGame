#include "rook.h"
#include "piece.h"

// Create a piece with name 'r'
Rook::Rook(int player) : Piece(player, 'r') {}

// Checks to see if a given move is valid
bool isMoveValid(int endX, int endY) const {
	if ( (endX - x) == 0 ||
			 (endY - y) == 0 ) {
		// Moves must be stright
		return true;
	}

  return false;
}
