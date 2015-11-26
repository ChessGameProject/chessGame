#include "game.h"

Game::Game(){

}

Game::~Game(){

}

void clearGame(){

}

bool isCheck(int player){
	if (player == WHITE){
		//Finds the Location the the King the the array of pieces and create pointer to it
		for (int i = 0; i < 16; i++){
			if (playerWhite[i]!= NULL && playerWhite[i]->getName() == 'K'){
				Piece *king = playerWhite[i];
				break;
			}
		}

		for (int i = 0; i < 16; i++){
			if (playerWhite[i] != king && playerWhite[i] != NULL){
				if (isPossibleMove(playerWhite[i]->x,playerWhite[i]->y,king->x,king->y){
					return true;
				}
			}
		}
		return false;

	}
	else if (player == BLACK){
		for (int i = 0; i < 16; i++){
			if (playerBlack[i]!= NULL && playerBlack[i]->getName() == 'k'){
				Piece *king = playerBlack[i];
				break;
			}
		}

		for (int i = 0; i < 16; i++){
			if (playerBlack[i] != king && playerBlack[i] != NULL){
				if (isPossibleMove(playerBlack[i]->x,playerBlack[i]->y,king->x,king->y){
					return true;
				}
			}
		}
		return false;

	}
	else return false;
}
