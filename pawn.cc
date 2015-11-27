#include "pawn.h"
#include "piece.h"

// Create a piece with name 'p'
Pawn::Pawn(int player) : Piece(player, 'p') {
	hasMoved = false;
	if (player == WHITE) {
		direction = 1;
	} else if (player == BLACK) {
		direction = -1;
	}
}

// Checks to see if a given move is valid
bool isMoveValid(int endX, int endY) const {
	bool tHasMoved = hasMoved;
	hasMoved = true;

	if ( !tHasMoved && 
		 (endX - x) == 0 &&
		 ( (endY - y) / direction ) == 2 )) {
		// Move two squares away from starting end on first move
	} else if ( (endX - x) == 0 &&
			 			( (endY - y) / direction ) == 1 ) {
		// Move one square away from starting end of the board
		return true;
	} else if ( (endX - x) == 1 &&
						( (endY - y) / direction ) == 1 ) {
		// Move one diagonal square away from starting end of the board
		//    - There must be a piece there
		//    - or **en passant**
		//game.hasPiece(endX, endY);

		// TODO: Check for EN PASSANT
		
		return true;
	}
  return false;
}
