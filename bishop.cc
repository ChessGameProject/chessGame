#include "bishop.h"
#include "game.h"
#include "piece.h"

// Create a piece with name 'b'
Bishop::Bishop(int player) : Piece(player, 'b') {}

// Checks if a given move is valid
bool Bishop::isMoveValid(int endX, int endY) const {
	// Moves must be diagonal
	if ( endX - x == endY - y ) {
		// Check that all places in between current and final location are empty

		// Determine direction 
		int xDir = 1;
		int yDir = 1;
		if (endX - x < 0) xDir = -1;
		if (endY - y < 0) yDir = -1;

		for (int i = x, j = y; (i != endX) && (j != endY); i += xDir, j += yDir) {
			// Make sure there are no pieces in the way
			if ( game->isOccupied(i, j) ) return false;
		}

		return true;
	}
  return false;
}
