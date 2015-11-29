#ifndef PIECE_H
#define PIECE_H

class Game;

class Piece {
protected:
	// Location of piece
	int x;
	int y;

	// Pointer to the current game, which will allow access to the board
	Game *game;

	// value of the piece to help with strategy selection
	int worth;
	// A single character name to represent the piece on the board
	char name;

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
