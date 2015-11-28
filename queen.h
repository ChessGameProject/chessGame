#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Queen : public Piece {
public:
	// Constructor with player the piece belongs too
	Queen(int player);

	// Checks to see if given move is valid
  bool isMoveValid(int endX, int endY) const;
};

#endif
