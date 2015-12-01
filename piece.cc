#include "game.h"
#include "piece.h"

// Change capitalization of the name based on player
Piece::Piece(int player, char name) {
	// if the piece belongs to the white player it should be capitalized
	hasMoved = false;

	if (player == WHITE) {
		this->name = name - 'a' + 'A';
	} else if (player == BLACK) {
		this->name = name;
	} else {
		// Player isn't recognized
		this->name = '!';
	}
}


// ========================
// Getters & Setters
// ========================

// Store game to connect with other functions
void Piece::setGame(Game * game) {
	this->game = game;
}

Game* Piece::getGame() const {
	return game;
}

// Store location of the piece
void Piece::setLocation(int x, int y) {
	this->x = x;
	this->y = y;
}

int Piece::getX() const {
	return x;
}

int Piece::getY() const {
	return y;
}

int Piece::getWorth() const {
	return worth;
}

char Piece::getName() const {
	return name;
}

// Should be called when piece is moved for the 1st time
void Piece::setHasMoved(bool moved) {
	hasMoved = moved;
}

//getter for hasMoved
bool Piece::getHasMoved(){
  	return hasMoved;
}

Piece::~Piece(){}