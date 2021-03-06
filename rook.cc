#include "rook.h"
#include "piece.h"
#include "game.h"

// Create a piece with name 'r'
Rook::Rook(int player) : Piece(player, 'r') {
	worth = ROOK;
}

// Checks to see if a given move is valid
bool Rook::isMoveValid(int endX, int endY) const {
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
	}
	else return false;

  return true;
}

