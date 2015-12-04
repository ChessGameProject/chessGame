#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
	// Different players pawns can only move in one direction
	//     -1 if starting at the top (black)
	//     1 if starting at the bottom (white)
	int direction;
public:
	// Constructor with player the piece belongs too
	Pawn(int player);

	// Checks to see if given move is valid
  bool isMoveValid(int endX, int endY) const;
};

#endif
