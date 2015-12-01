#include "queen.h"
#include "piece.h"
#include "game.h"

// Create a piece with name 'q'
Queen::Queen(int player) : Piece(player, 'q') {
	worth = QUEEN;
}

// Checks if a given move is valid
bool Queen::isMoveValid(int endX, int endY) const {
	// Moves must be square or diagonal
	
	if ( (endX - x) == 0 ) {
		// Straight up and down
		
		// Determine direction 
		int yDir = 1;
		if (endY - y < 0) yDir = -1;

		for ( int i = y + yDir; i != endY; i += yDir ) {
			// Make sure there are no pieces in the way
			if ( game->isOccupied(x, i) ) return false;
		}

	} else if ( (endY - y) == 0 ) {
		// Stright right or left

			// Determine direction 
		int xDir = 1;
		if (endX - x < 0) xDir = -1;

		for ( int i = x + xDir; i != endX; i += xDir ) {
			// Make sure there are no pieces in the way
			if ( game->isOccupied(i, y) ) return false;
		}

	} else if ( std::abs(endX - x) == std::abs(endY - y) ) {
		// Diagonal

		// Determine direction 
		int xDir = 1;
		int yDir = 1;
		if (endX - x < 0) xDir = -1;
		if (endY - y < 0) yDir = -1;

		for (int i = x + xDir, j = y + yDir; (i != endX) && (j != endY); i += xDir, j += yDir) {
			// Make sure there are no pieces in the way
			if ( game->isOccupied(i, j) ) return false;
		}
	}
	else return false;

  return true;
}
