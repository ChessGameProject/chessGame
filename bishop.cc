#include "bishop.h"
#include "piece.h"

// Create a piece with name 'b'
Bishop::Bishop(int player) : Piece(player, 'b') {}

// Checks if a given move is valid
bool Bishop::isMoveValid(int endX, int endY) const {
	if ( endX - x == endY - y ) {
		// Moves must be diagonal
		return true;
	}
  return false;
}
