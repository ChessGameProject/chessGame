#include "rook.h"
#include "piece.h"

// Create a piece with name 'r'
Rook::Rook(int player) : Piece(player, 'r') {}

// Checks to see if a given move is valid
bool Rook::isMoveValid(int endX, int endY) const {
	if ( (endX - x) == 0 ) {
		// Straight up and down
		
		// Determine direction 
		int yDir = 1;
		if (endY - y < 0) yDir = -1;

		for ( int i = y; i != endY; i += yDir ) {
			if ( game.isOccupied(x, i) ) return false;
		}

	} else if ( (endY - y) == 0 ) {
		// Stright right or left
		return true;
	}

  return false;
}
