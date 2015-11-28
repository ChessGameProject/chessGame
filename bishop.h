#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop : public Piece {
public:
	// Constructor with player the piece belongs too
	Bishop(int player);

	// Checks to see if given move is valid
  bool isMoveValid(int endX, int endY) const;
};

#endif
