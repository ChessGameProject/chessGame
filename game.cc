#include "game.h"

Game::Game(){

}

Game::~Game(){

}

void Game::clearGame(){

}


bool Game::isPossibleMove(int startX, int startY, int endX, int endY){

	if (startX > 7 || startX < 0 || startY > 7 || startY < 0 || endX < 0 || endX > 7 || endY > 7 || endY < 0) return false;
	if (startX == endX && startY == endY) return false;

	//Checks if the Move is valid based on the isMoveValid() function from the Piece class
	if (theBoard[startX][startY]->getPiece()->isMoveValid(startX,startY,endX,endY) == false) return false;

	//Now for each piece, we need to check if their path is blocked on the board

	//Since Knights only can move in certain ways, if it passes the Piece isMoveValid(), it is valid
	if (theBoard[startX][startY]->getPiece()->getName() == 'n' || 
		theBoard[startX][startY]->getPiece()->getName()== 'N') return true;


	//Check for the King
	if (theBoard[startX][startY]->getPiece()->getName() == 'k' || 
		theBoard[startX][startY]->getPiece()->getName() == 'K'){
		//Check for Castle??????
		return true;

	}




	// Checks that the pawn's move is valid
	if (theBoard[startX][startY]->getPiece()->getName() == 'p' || theBoard[startX][startY]->getPiece()->getName()me == 'P'){
		//Case if pawn is moving forward, not capturing
		if (endX == endY){
			//Checks that the space it is moving to is empty
			if (theBoard[endX][endY]->getPiece() == NULL) return true;
			else return false;
		}
		//Checks that the space it is moving to is occupied by opposing piece
		else{
			if (theBoard[endX][endY]->getPiece() == NULL) return false;
			else{
				//If the piece is White
				if(theBoard[startX][startY]->getName() >= 'A'){
					// If it finds the piece that is in the location the pawn is moving to is an enemy piece
					// it returns true. otherwise the returns false
					for (int i = 0; i < 16; i++){
						if (playerBlack[i] == theBoard[endX][endY]->getPiece()){
							return true;
						}
					}
					return false;
				}

				//if the piece is Black
				else{
					for (int i = 0; i < 16; i++){
						if (playerWhite[i] == theBoard[endX][endY]->getPiece()){
							return true;
						}
					}
					return false;
				}
			}
		}
	}

	//Checks that bishop move is valid
	if (theBoard[startX][startY]->getPiece()->getName() == 'b' || theBoard[startX][startY]->getPiece()->getName() == 'B'){
		// Bishop is moving the the right
		if (endX > startX){
			for (int i = 1; i < endX - startX; i++){
				// Bishop is moving diagonaly up to the right
				if (endY > startY){
					if (theBoard[startX + i][startY + i]->getPiece() != NULL) return false;
				}
				// Bishop is moving down to the right
				else{
					if (theBoard[startX + i][startY - i]->getPiece() != NULL) return false;	
				}
			}
		}

		// Bishop is moving to the left
		else{
		for (int i = 1; i < startX - endX; i++){
				// Bishop is moving diagonaly up to the right
				if (endY > startY){
					if (theBoard[startX - i][startY + i]->getPiece() != NULL) return false;
				}
				// Bishop is moving down to the right
				else{
					if (theBoard[startX - i][startY - i]->getPiece() != NULL) return false;	
				}
			}
		}
		return true;
	}

	//If Piece is a Rook
	if (theBoard[startX][startY]->getPiece()->getName() == 'r' || theBoard[startX][startY]->getPiece()->getName() == 'R'){
		// rook is moving vertically
		if (startX == endX){
			// Rook is moving up
			if (startY < endY){
				for (int i = 1; i < endY - startY; i++){
					if (theBoard[startY + i][startX]->getPiece()!= NULL) return false;
				}	
			}
			//Rook is moving down
			else{
				for (int i = 1; i < startY - endY; i++){
					if (theBoard[startY - i][startX]->getPiece()!= NULL) return false;
				}
			}
		}

		// Rook is moving horizontally
		else{
			// Rook is to the right
			if (startX < endX){
				for (int i = 1; i < endX - startX; i++){
					if (theBoard[startY][startX + i]->getPiece()!= NULL) return false;
				}	
			}
			//Rook is to the left
			else{
				for (int i = 1; i < startX - endX; i++){
					if (theBoard[startY][startX - i]->getPiece()!= NULL) return false;
				}
			}

		}
		return true;

	}

	//If Piece is a Queen
	if (theBoard[startX][startY]->getPiece()->getName() == 'q' || theBoard[startX][startY]->getPiece()->getName() == 'Q'){
		//Queen is moving diagonally
		if (startX-endX == startY-endY){
			// Queen is moving to the right diagonally
			if (endX > startX){
				for (int i = 1; i < endX - startX; i++){
					// Queen is moving diagonaly up to the right
					if (endY > startY){
						if (theBoard[startX + i][startY + i]->getPiece() != NULL) return false;
					}
					// Queen is moving down to the right
					else{
						if (theBoard[startX + i][startY - i]->getPiece() != NULL) return false;	
					}
				}
			}

			// Queen is moving to the left diagonally
			else{
			for (int i = 1; i < startX - endX; i++){
					// Queen is moving diagonaly up to the right
					if (endY > startY){
						if (theBoard[startX - i][startY + i]->getPiece() != NULL) return false;
					}
					// Queen is moving down to the right
					else{
						if (theBoard[startX - i][startY - i]->getPiece() != NULL) return false;	
					}
				}
			}
		}
		//Queen is moving horizontally or vertically
		else{
			// Queen is moving vertically
			if (startX == endX){
				// Queen is moving up
				if (startY < endY){
					for (int i = 1; i < endY - startY; i++){
						if (theBoard[startY + i][startX]->getPiece()!= NULL) return false;
					}	
				}
				//Queen is moving down
				else{
					for (int i = 1; i < startY - endY; i++){
						if (theBoard[startY - i][startX]->getPiece()!= NULL) return false;
					}
				}
			}

			// Queen is moving horizontally
			else{
				// Queen is to the right
				if (startX < endX){
					for (int i = 1; i < endX - startX; i++){
						if (theBoard[startY][startX + i]->getPiece()!= NULL) return false;
					}	
				}
				//Queen is to the left
				else{
					for (int i = 1; i < startX - endX; i++){
						if (theBoard[startY][startX - i]->getPiece()!= NULL) return false;
					}
				}
			}
		}
		return true;
	}

	// Fail safe if none of the if statements are called, then it just returns false
	return false;
}

bool Game::isValidMove(int startX, int startY, int endX, int endY){

	if (isPossibleMove(startX,startY,endX,endY) == false) return false;

	//Check for castle

	//Check for en passant

	//Check for moving into check

}

bool Game::isOccupied(int x, int y){
	if (theBoard[x][y] == NULL) return false;
	else return true;
}

bool Game::isCheckmate(int player){

}

bool Game::isStalemate(int player){

	if (player == WHITE){
		for (int i = 0; i < 16; i++){
			if (playerWhite[i] == NULL) continue;
			for(int x = 0; x < 8; x++){
				for(int y = 0; y < 8; y++){
					if (isMoveValid(playerWhite[i]->getX(),playerWhite[i]->getY(),x,y) == true) return false;
				}
			}
		}
	}
	else{
		for (int i = 0; i < 16; i++){
			if (playerBlack[i] == NULL) continue;
			for(int x = 0; x < 8; x++){
				for(int y = 0; y < 8; y++){
					if (isMoveValid(playerBlack[i]->getX(),playerBlack[i]->getY(),x,y) == true) return false;
				}
			}
		}
	}
	return true;
}

bool Game::isCheck(int player){
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
				if (isPossibleMove(playerWhite[i]->getX(),playerWhite[i]->getY(),king->getX(),king->getY()){
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
				if (isPossibleMove(playerBlack[i]->getX(),playerBlack[i]->getY(),king->getX(),king->getY()){
					return true;
				}
			}
		}
		return false;

	}
	else return false;
}

bool Game::makeMove(int startX, int startY, int endX, int endY){
	if (isValidMove(startX,startY,endX,endY) == false) return false;


	//******Will this work??????*******//
	//I want to delete the piece if it is being eaten
	if (theBoard[endX][endY]->getPiece != NULL) delete theBoard[endX][endY]->getPiece();

	//Check for Pawn Promotion

	//If eating piece, check to see if eating own piece

	theBoard[endX][endY]->setPiece(theBoard[startX][startY]);
	theBoard[start][startY]->setPiece(NULL);

}
