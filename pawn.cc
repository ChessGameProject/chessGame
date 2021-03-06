#include "pawn.h"
#include "piece.h"
#include "game.h"
#include <iostream>

// Create a piece with name 'p'
Pawn::Pawn(int player) : Piece(player, 'p') {
	hasMoved = false;
	worth = PAWN;
	direction = -1 * player;
}

// Checks to see if a given move is valid
bool Pawn::isMoveValid(int endX, int endY) const {
	// #ifdef DEBUG
	//     std::cout << "    (Pawn)" << std::endl;
	//     std::cout << "       chgX: " << endX - x;
	//     std::cout << "   chgY: " << (endY - y) / direction << " " << "dir:" << direction << std::endl;
	// #endif
	if ( !hasMoved && 
		 (endX - x) == 0 &&
		 ( (endY - y) / direction ) == 2 
		 && !game->isOccupied(endX,endY) ) {

		return true;
	} else if ( (endX - x) == 0 &&
			 			  ( ( (endY - y) / direction ) == 1 ) &&
			 			  ( !game->isOccupied(endX, endY)) ) {
		// Move one square away from starting end of the board
		return true;
	} else if ( std::abs(endX - x) == 1 &&
						  ( (endY - y) / direction ) == 1 &&
						  ( game->isOccupied(endX, endY) || game->enPassantPossible(endX,endY) ) ) {
		// Move one diagonal square away from starting end of the board
		//    - There must be a piece there
		//    - or **en passant**
				
		return true;
	}
	return false;
}
