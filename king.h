#ifndef KING_H
#define KING_H
#include "piece.h"

class King : public Piece {
public:
	// Constructor with player the piece belongs too
	King(int player);

	// Checks to see if given move is valid
  bool isMoveValid(int endX, int endY) const;
};

#endif
