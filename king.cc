#include "king.h"
#include "piece.h"

// Create a piece with name 'k'
King::King(int player) : Piece(player, 'k') {
	hasMoved = false;
}

// Checks if a given move is valid
bool isMoveValid(int endX, int endY) const {
	if ( !hasMoved && ( x - endX == 2 ) ) { // Is moving two to the left	
		// Check Castling
		return true;
	} else if ( ( std::abs(endX-x) <= 1 ) && ( std::abs(endY - y) <= 1 ) ) {
		// Otherwise only move one square in any direction
		return true;
	}

	return false;
}
