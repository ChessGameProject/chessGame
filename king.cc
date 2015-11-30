#include "king.h"
#include "piece.h"
#include <iostream>

// Create a piece with name 'k'
King::King(int player) : Piece(player, 'k') {
	hasMoved = false;
	worth = KING;
}

// Checks if a given move is valid
bool King::isMoveValid(int endX, int endY) const {
	if ( std::abs(x - endX) == 2  || std::abs(x - endX) == 3) { // Is moving two or three laterally
		// Commence Castling Check


		//If not moving on same y-cais, invalid castle move
		if (y != endY) return false;

		//Cannot castle when not on either the top or bottom row
		if (y != 7 && y != 0) return false;

		// Check that king hasn't moved
		if (hasMoved) return false;

		// Determine direction
		int dir = 1
		if (endX - x < 0) dir = -1;

		//Checks if King is moving enough spaces in the correct direction
		if (dir == 1 && std::abs(x - endX) == 3) return false;
		if (dir == -1 && std::abs(x - endX) == 2) return false;

		// TODO: Check the rook in that direction has not moved

		// Check pieces between king and rook
		for (int i = x; ((x > 0) && (x < 8)); x += dir) {
			if game.isOccupied(i, y) return false;
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

//getter for hasMoved
bool King::getHasMoved(){
  	return hasMoved;
}
