#include "knight.h"
#include "piece.h"

// Create a piece with name 'n'
Knight::Knight(int player) : Piece(player, 'n') {}

/* Checks if a given move is valid
 * A knight should only move in an 'L' shape of type 1 or 2
 *     - - 1 - 1 - -
 *     - 2 - - - 2 -
 *     - - - N - - -
 *     - 2 - - - 2 -
 *     - - 1 - 1 - -
 */

bool isMoveValid(int endX, int endY) const {
	if ( (std::abs(endX - x) == 1 && 		// Type 1
				std::abs(endY - y) == 2) ||
				(std::abs(endX - x) == 2 &&		// Type 2
				std::abs(endY - y) == 1) ) {
		// Moves must be L-shaped
		return true;
	}
  return false;
}
