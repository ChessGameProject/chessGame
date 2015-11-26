#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Knight : public Piece {
public:
	// Constructor with player the piece belongs too
	Knight(int player);

	// Checks to see if given move is valid
  bool isMoveValid(int startX, int startY, int endX, int endY) const;
};

#endif
