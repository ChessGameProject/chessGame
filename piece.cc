#include "game.h"
#include "piece.h"

// Change capitalization of the name based on player
Piece::Piece(int player, char name) {
	// if the piece belongs to the white player it should be capitalized
	if (player == WHITE) {
		this->name = name - 'a' + 'A';
	} else {
		this->name = name;
	}
}


// ========================
// Getters & Setters
// ========================

Piece::setGame(Game game) {
	this->game = game;
}

Game Piece::getGame() {
	return game;
}

int Piece::getWorth() {
	return worth;
}

char Piece::getName() {
	return name;
}
