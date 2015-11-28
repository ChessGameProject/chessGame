#include "game.h"

Game::Game(){

}

Game::~Game(){

}

void Game::clearGame(){

}


bool Game::isPossibleMove(int startX, int startY, int endX, int endY){

	// Fail safe if none of the if statements are called, then it just returns false
	return false;
}

bool Game::isValidMove(int startX, int startY, int endX, int endY){

	return false;
	//Check for castle

	//Check for en passant

	//Check for moving into check

}

bool Game::isOccupied(int x, int y){
	return false;
}

bool Game::isCheckmate(int player){
	return false;
}

bool Game::isCheck(int player){
	// placeholder
	return false;
}

bool Game::makeMove(int startX, int startY, int endX, int endY, char pawnPromotionPiece){
	return false;

}
