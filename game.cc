#include "game.h"
/*
TO DO:
- Castling
- En Passant
- setup() function
- checkMate()
- clearGame()
*/



Game::Game(){
	//Sets all pieces in Board to NULL
	for(int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			theBoard[i][j] = NULL;
		}
	}

	for (int i = 0; i < 25; i++){
		playerWhite[i] = NULL;
		playerBlack[i] = NULL;
	}
	
	p1Score = 0;
	p2Score = 0;
	notifications = this;
	currentPlayer = WHITE;
	pawnPromote = false;
	promoteType = '';

}

Game::~Game(){
	for(int i = 0; i < 8; i++){
		delete [] theBoard[i];
	}
	delete [] theBoard;

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

bool isCheckAfterMove(int startX, int startY, int endX, int endY){
	Piece* temp = theBoard[endX][endY];
	makeMove(startX,startY,endX,endY,'',false);
	bool output = false;
	if (isCheck() == true) output = true;
	makeMove(endX,endY,startX,startY,'',false);
	theBoard[endX][endY] = temp;
	return output;
}

bool Game::isValidMove(int startX, int startY, int endX, int endY){
	//Checks if input is valid
	if (startX > 7 || startX < 0 || startY > 7 || startY < 0 || endX < 0 || endX > 7 || endY > 7 || endY < 0) return false;
	if (startX == endX && startY == endY) return false;

	//If there is no piece at the specified location, returns false
	if (theBoard[startX][startY] == NULL) return false;

	//Check is Move is invalid from the Piece class
	if (theBoard[startX]start[Y]->isMoveValid(endX,endY) == false) return false;


	//Check for castle

	//Check for en passant

	//Check for moving into check

}

bool Game::isOccupied(int x, int y){
	if (theBoard[x][y] == NULL) return false;
	else return true;
}

bool Game::isCheckmate(){
	//Finds the Location the the King the the array of pieces and create pointer to it
	if (getCurrentPlayer() == BLACK){
		for (int i = 0; i < 25; i++){
			if (playerWhite[i] != NULL && playerWhite[i]->getName() == 'K'){
				Piece *king = playerBlack[i];
				break;
			}
		}
	}
	else{
		for (int i = 0; i < 25; i++){
			if (playerBlack[i] != NULL && playerBlack[i]->getName() == 'k'){
				Piece *king = playerWhite[i];
				break;
			}
		}
	}

	//For all possible moves around the king, it checks if after moving the king there would result in a Check position
	for (int x = -1; x <= 1; x++){
		for (int y = -1; y <= 1; y++){
			(isCheckAfterMove(king->getX(),king->getY(),king->getX() + x,king->getY() + y) == false) return false;
		}
	}
	return true;
}

bool Game::isStalemate(){

	if (getCurrentPlayer() == WHITE){
		//goes through each piece and trie to find a valid move for any piece
		for (int i = 0; i < 16; i++){
			if (playerWhite[i] == NULL) continue;
			for(int x = 0; x < 8; x++){
				for(int y = 0; y < 8; y++){
					//If it can find a valid move for the current player, returns false since it is not a stalemate
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

bool Game::isCheck(){
	if (getCurrentPlayer() == BLACK){
		//Finds the Location the the King the the array of pieces and create pointer to it
		for (int i = 0; i < 25; i++){
			if (playerWhite[i] != NULL && playerWhite[i]->getName() == 'K'){
				Piece *king = playerBlack[i];
				break;
			}
		}

		//Goes through each opposition player and sees if any of them can make a vlid move to the King
		for (int i = 0; i < 25; i++){
			if (playerWhite[i] != king && playerWhite[i] != NULL){
				if (playerWhite[i]->isMoveValid(king->getX(),king->getY()) == true){
					return true;
				}
			}
		}
		return false;

	}
	else{
		for (int i = 0; i < 25; i++){
			if (playerBlack[i] != NULL && playerBlack[i]->getName() == 'k'){
				Piece *king = playerWhite[i];
				break;
			}
		}

		for (int i = 0; i < 25; i++){
			if (playerBlack[i] != king && playerBlack[i] != NULL){
				if (playerBlack[i]->isMoveValid(king->getX(),king->getY())){
					return true;
				}
			}
		}
		return false;

	}
}

bool Game::makeMove(int startX, int startY, int endX, int endY, char promoteType = '', bool checkForCheck = true){
	if (isValidMove(startX,startY,endX,endY) == false) return false;

	//Checks to see if piece that it is moving to its own piece
	for (int i = 0; i < 25; i++){
		if (currentPlayer() == WHITE){
			if(playerWhite[i] == theBoard[endX][endY]) return false;
		}
		else{
			if(playerBlack[i] == theBoard[endX][endY]) return false;
		}
	}

	//Check for Check
	if (checkForCheck == true){
		if (isCheckAfterMove(startX,startY,endX,endY) == true) return false;
	}


	//Checks for Pawn Promotion,
	if (promoteType != ''){
		// Check if character is correct Case
		if (promoteType > 'A') promoteType = promoteType - 'A' + 'a';

		//Finds location of piece in the array of pieces
		int loc = 16;
		if (getCurrentPlayer() == WHITE){	
			while(playerWhite[loc] != NULL){
				++loc;
			}
		}
		else{
			while(playerBlack[loc] != NULL){
				++loc;
			}
		}

		if (getPromoteType() == 'q'){
			if (getCurrentPlayer() = WHITE){
				playerWhite[loc] = new Queen(WHITE);
				playerWhite[loc].setGame(this);
				playerWhite[loc].setLocation(startX,startY);
				theBoard[startX][startY] = playerWhite[loc];
			}
			else{
				playerBlack[loc] = new Queen(BLACK);
				playerBlack[loc].setGame(this);
				playerBlack[loc].setLocation(startX,startY);
				theBoard[startX][startY] = playerBlack[loc];
			}
		}
		else if (getPromoteType() == 'r'){
			if (getCurrentPlayer() = WHITE){
				playerWhite[loc] = new Rook(WHITE);
				playerWhite[loc].setGame(this);
				playerWhite[loc].setLocation(startX,startY);
				theBoard[startX][startY] = playerWhite[loc];
			}
			else{
				playerBlack[loc] = new Rook(BLACK);
				playerBlack[loc].setGame(this);
				playerBlack[loc].setLocation(startX,startY);
				theBoard[startX][startY] = playerBlack[loc];
			}
		}
		else if (getPromoteType() == 'b'){
			if (getCurrentPlayer() = WHITE){
				playerWhite[loc] = new Bishop(WHITE);
				playerWhite[loc].setGame(this);
				playerWhite[loc].setLocation(startX,startY);
				theBoard[startX][startY] = playerWhite[loc];
			}
			else{
				playerBlack[loc] = new Bishop(BLACK);
				playerBlack[loc].setGame(this);
				playerBlack[loc].setLocation(startX,startY);
				theBoard[startX][startY] = playerBlack[loc];
			}
		}
		else if (getPromoteType() == 'n'){
			if (getCurrentPlayer() = WHITE){
				playerWhite[loc] = new Knight(WHITE);
				playerWhite[loc].setGame(this);
				playerWhite[loc].setLocation(startX,startY);
				theBoard[startX][startY] = playerWhite[loc];
			}
			else{
				playerBlack[loc] = new Knight(BLACK);
				playerBlack[loc].setGame(this);
				playerBlack[loc].setLocation(startX,startY);
				theBoard[startX][startY] = playerBlack[loc];
			}
		}
	}


	//For Kings and Rooks, if they have not moved before, setHasMoved to true;
	if (theBoard[startX][startY]->getChar == 'k' || theBoard[startX][startY]->getChar == 'K' ||
		theBoard[startX][startY]->getChar == 'r' || theBoard[startX][startY]->getChar == 'R'){
		if (theBoard[startX][startY]->getHasMoved == false) theBoard[startX][startY]->setHasMoved(true);
	}

	theBoard[endX][endY] = theBoard[startX][startY];
	if (checkForCheck)theBoard[start][startY]->setLocation(-1,-1);
	theBoard[start][startY] = NULL;
	theBoard[endX][endY].setLocation(endX,endY);

	//Notifies of changes
	notify(startX,startY,'');
	notify(endX,endY, theBoard[endX][endY]->getChar());

}

int Game::getCurrentPlayer(){
	return currentPlayer;
}

char Game::getPromoteType(){
	return promoteType;
}

void Game::setPawnPromote(bool promote){
	pawnPromote = promote;
}

void Game::setPromoteType(char type){
	promoteType = type;
}

void initialSetup(){
	//Sets initial location of Pawns
	for (int i = 0; i < 8; i++){
		playerWhite[i] = new Pawn(WHITE);
		playerBlack[i] = new Pawn(BLACK);
		playerWhite[i]->setGame(this);
		playerBlack[i]->setGame(this);
		playerWhite[i]->setLocation(i,7);
		playerWhite[i]->setLocation(i,2);
		theBoard[i][7] = playerWhite[i];
		theBoard[i][2] = playerBlack[i];
	}

	//Sets Location of Rooks
	theBoard[0][0] = new Rook(BLACK);
	theBoard[7][0] = new Rook(BLACK);
	theBoard[0][7] = new Rook(WHITE);
	theBoard[7][7] = new Rook(WHITE);

	playerBlack[8] = theBoard[0][0];
	playerBlack[9] = theBoard[7][0];
	playerWhite[8] = theBoard[0][7];
	playerWhite[9] = theBoard[7][7];

	theBoard[0][0]->setGame(this);
	theBoard[7][0]->setGame(this);
	theBoard[0][7]->setGame(this);
	theBoard[7][7]->setGame(this);

	theBoard[0][0]->setLocation(0,0);
	theBoard[7][0]->setLocation(7,0);
	theBoard[0][7]->setLocation(0,7);
	theBoard[7][7]->setLocation(7,7);

	//Sets Location of Knights
	theBoard[1][0] = new Knight(BLACK);
	theBoard[6][0] = new Knight(BLACK);
	theBoard[1][7] = new Knight(WHITE);
	theBoard[6][7] = new Knight(WHITE);

	playerBlack[10] = theBoard[1][0];
	playerBlack[11] = theBoard[6][0];
	playerWhite[10] = theBoard[1][7];
	playerWhite[11] = theBoard[6][7];

	theBoard[1][0]->setGame(this);
	theBoard[6][0]->setGame(this);
	theBoard[1][7]->setGame(this);
	theBoard[6][7]->setGame(this);

	theBoard[1][0]->setLocation(1,0);
	theBoard[6][0]->setLocation(6,0);
	theBoard[1][7]->setLocation(1,7);
	theBoard[6][7]->setLocation(6,7);

	//Sets Location of Bishops
	theBoard[2][0] = new Bishop(BLACK);
	theBoard[5][0] = new Bishop(BLACK);
	theBoard[2][7] = new Bishop(WHITE);
	theBoard[5][7] = new Bishop(WHITE);

	playerBlack[12] = theBoard[2][0];
	playerBlack[13] = theBoard[5][0];
	playerWhite[12] = theBoard[2][7];
	playerWhite[13] = theBoard[5][7];

	theBoard[2][0]->setGame(this);
	theBoard[5][0]->setGame(this);
	theBoard[2][7]->setGame(this);
	theBoard[5][7]->setGame(this);

	theBoard[2][0]->setLocation(2,0);
	theBoard[5][0]->setLocation(5,0);
	theBoard[2][7]->setLocation(2,7);
	theBoard[5][7]->setLocation(5,7);

	//Sets Location fo Queens
	theBoard[3][0] = new Queen(BLACK);;
	theBoard[3][7] = new Queen(WHITE);

	playerBlack[14] = theBoard[3][0];
	playerWhite[14] = theBoard[3][7];

	theBoard[3][0]->setGame(this);
	theBoard[3][7]->setGame(this);

	theBoard[3][0]->setLocation(3,0);
	theBoard[3][7]->setLocation(3,7);

	//Sets Location of King
	theBoard[4][0] = new King(BLACK);;
	theBoard[4][7] = new King(WHITE);

	playerBlack[15] = theBoard[4][0];
	playerWhite[15] = theBoard[4][7];

	theBoard[4][0]->setGame(this);
	theBoard[4][7]->setGame(this);

	theBoard[4][0]->setLocation(4,0);
	theBoard[4][7]->setLocation(4,7);
}

void setup(){
	initialSetup();
}
