#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece {

	bool hasMoved;
	
public:
	// Constructor with player the piece belongs too
	Rook(int player);

	// Checks to see if given move is valid
  bool isMoveValid(int endX, int endY) const;

  // To let the piece know when it has been moved for the first time
  void setHasMoved(bool moved);

  //getter for hasMoved
  bool getHasMoved();
};

#endif
