#ifndef PIECE_H
#define PIECE_H

class Game;

const int WHITE = 1;
const int WHITE = 1;
const int BLACK = 2;
const int KING = -1;
const int QUEEN = 900;
const int ROOK = 500;
const int BISHOP = 305;
const int KNIGHT = 300;
const int PAWN = 100;

class Piece {
	// Pointer to the current game, which will allow access to the board
	Game *game;

	// value of the piece to help with strategy selection
	//King: -1
	//Queen: 900
	//Rook: 500
	//Bishop: 305
	//Knight: 300
	//Pawn: 100
	int worth;
	// A single character name to represent the piece on the board
	char name;
	
protected:
	// Location of piece
	int x;
	int y;

public:
	// Constructor that changes capitalization of the name based on player
	Piece(int player, char name);

	// Allow game to be set
	void setGame(Game * game);
	Game* getGame() const;

	// Get and set location
	void setLocation(int x, int y);
	int getX() const;
	int getY() const;
  	
	// worth and name will be set by individual piece constructors, not client
	int getWorth() const;
	char getName() const;

	// Checks to see if given move is valid
  virtual bool isMoveValid(int endX, int endY) const = 0;
};

#endif
