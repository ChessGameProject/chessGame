#include "king.h"
#include "game.h"
#include "piece.h"
#include <iostream>

// Create a piece with name 'k'
King::King(int player) : Piece(player, 'k') {
	hasMoved = false;
}

// Checks if a given move is valid
bool King::isMoveValid(int endX, int endY) const {
	if ( std::abs(x - endX) == 2 ) { // Is moving two
		// Commence Castling Check

		// Check that king hasn't moved
		if (hasMoved) return false;

		// Determine direction
		int dir = 1;
		if (endX - x < 0) dir = -1;

		// TODO: Check the rook in that direction has not moved

		// Check pieces between king and rook
		for (int i = x; ((i > 0) && (i < 8)); i += dir) {
			if ( game->isOccupied(i, y) ) return false;
		}

		// TODO: Check that king isn't currently in check

		// TODO: Check that squares the King WOULD pass through would not
		//    place the King in check

		return true;
	} else if ( ( std::abs(endX-x) <= 1 ) && ( std::abs(endY - y) <= 1 ) ) {
		// Otherwise only move one square in any direction
		return true;
	}

	return false;
}

// Should be called when piece is moved for the 1st time
void King::setHasMoved(bool moved) {
	hasMoved = moved;
}
