#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece {
public:
	// Constructor with player the piece belongs too
	Rook(int player);

	// Checks to see if given move is valid
  bool isMoveValid(int endX, int endY) const;
};

#endif
