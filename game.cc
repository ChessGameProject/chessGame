#include "game.h"
#include "piece.h"
#include <iostream>

using namespace std;
/*
TO DO:
- En Passant
- setup() function
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
	currentPlayer = WHITE;
}

Game::~Game(){
	clearGame();
}

void Game::notify(int x, int y, char c){
	notifications->notify(x,y,c);
}

void Game::clearGame(){
	delete [] playerWhite;
	delete [] playerBlack;
	delete [] theBoard;
	notifications = NULL;
	p1Score = 0;
	p2Score = 0;
}

bool Game::isCheckAfterMove(int startX, int startY, int endX, int endY, int player){
	Piece* temp = theBoard[endX][endY];
	makeMove(startX,startY,endX,endY,' ',false);
	bool output = false;
	if (isCheck(player) == true) output = true;
	makeMove(endX,endY,startX,startY,' ',false);
	theBoard[endX][endY] = temp;
	return output;
}

bool Game::isCheckAfterMove(int startX, int startY, int endX, int endY){
	isCheckAfterMove(startX,startY, endX, endY, currentPlayer);
}

bool Game::isValidMove(int startX, int startY, int endX, int endY){
	//Checks if input is valid
	if (startX > 7 || startX < 0 || startY > 7 || startY < 0 || endX < 0 || endX > 7 || endY > 7 || endY < 0) return false;
	if (startX == endX && startY == endY) return false;

	//If there is no piece at the specified location, returns false
	if (isOccupied(startX,startY) == false) return false;

	//Check is Move is invalid from the Piece class
	if (theBoard[startX][startY]->isMoveValid(endX,endY) == false) return false;


	//Check for castle
	if (currentPlayer = WHITE){

	}
	else{

	}


	//Check for en passant

}

bool Game::isOccupied(int x, int y){
	if (theBoard[x][y] == NULL) return false;
	else return true;
}

bool Game::isCheckmate(){
	//Finds the Location the the King the the array of pieces and create pointer to it
	int player;
	Piece *king;
	if (getCurrentPlayer() == WHITE){
		for (int i = 0; i < 25; i++){
			if (playerBlack[i] != NULL && playerBlack[i]->getWorth() == KING){
				king = playerBlack[i];
				player = BLACK;
				break;
			}
		}
	}
	else{
		for (int i = 0; i < 25; i++){
			if (playerWhite[i] != NULL && playerWhite[i]->getWorth() == KING){
				king = playerWhite[i];
				player = WHITE;
				break;
			}
		}
	}

	//For all possible moves around the king, it checks if after moving the king there would result in a Check position
	for (int x = -1; x <= 1; x++){
		for (int y = -1; y <= 1; y++){
			if (isCheckAfterMove(king->getX(),king->getY(),king->getX() + x,king->getY() + y, player) == false) return false;
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
					if (isValidMove(playerWhite[i]->getX(),playerWhite[i]->getY(),x,y) == true) return false;
				}
			}
		}
	}
	else{
		for (int i = 0; i < 16; i++){
			if (playerBlack[i] == NULL) continue;
			for(int x = 0; x < 8; x++){
				for(int y = 0; y < 8; y++){
					if (isValidMove(playerBlack[i]->getX(),playerBlack[i]->getY(),x,y) == true) return false;
				}
			}
		}
	}
	return true;
}

bool Game::hasWon(){
	return isCheckmate();
}

bool Game::isCheck(int player){
	Piece* king;
	if (player == WHITE){
		//Finds the Location the the King the the array of pieces and create pointer to it
		for (int i = 0; i < 25; i++){
			if (playerWhite[i] != NULL && playerWhite[i]->getWorth() == KING){
				king = playerWhite[i];
				break;
			}
		}

		//Goes through each opposition player and sees if any of them can make a valid move to the King
		for (int i = 0; i < 25; i++){
			if (playerBlack[i] != NULL){
				if (playerBlack[i]->isMoveValid(king->getX(),king->getY()) == true){
					return true;
				}
			}
		}
	}
	else{
		for (int i = 0; i < 25; i++){
			if (playerBlack[i] != NULL && playerBlack[i]->getWorth() == KING){
				king = playerBlack[i];
				break;
			}
		}

		for (int i = 0; i < 25; i++){
			if (playerWhite[i] != NULL){
				if (playerWhite[i]->isMoveValid(king->getX(),king->getY())){
					return true;
				}
			}
		}
	}
	return false;
}

bool Game::isCheck(){
	isCheck(currentPlayer);
}
bool Game::makeMove(int startX, int startY, int endX, int endY, char promoteType, bool checkForCheck){
	if (isValidMove(startX,startY,endX,endY) == false) return false;

	//Checks to see if piece that it is moving to its own piece
	for (int i = 0; i < 25; i++){
		if (currentPlayer == WHITE){
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
	if (promoteType != ' '){

		//Checks that the piece is a pawn moving to the end row
		if (theBoard[startX][startY]->getWorth() != PAWN) return false;
		if (currentPlayer == WHITE && endY != 0) return false;
		if (currentPlayer == BLACK && endY != 7) return false;



		// Check if character is correct Case
		if (promoteType > 'A') promoteType = promoteType - 'A' + 'a';

		//Finds location of piece in the array of pieces
		int loc = 16;
		if (currentPlayer == WHITE){	
			while(playerWhite[loc] != NULL){
				++loc;
			}
		}
		else{
			while(playerBlack[loc] != NULL){
				++loc;
			}
		}

		if (promoteType == 'q'){
			if (currentPlayer == WHITE){
				playerWhite[loc] = new Queen(WHITE);
				playerWhite[loc]->setGame(this);
				playerWhite[loc]->setLocation(startX,startY);
				theBoard[startX][startY] = playerWhite[loc];
			}
			else{
				playerBlack[loc] = new Queen(BLACK);
				playerBlack[loc]->setGame(this);
				playerBlack[loc]->setLocation(startX,startY);
				theBoard[startX][startY] = playerBlack[loc];
			}
		}
		else if (promoteType == 'r'){
			if (currentPlayer == WHITE){
				playerWhite[loc] = new Rook(WHITE);
				playerWhite[loc]->setGame(this);
				playerWhite[loc]->setLocation(startX,startY);
				theBoard[startX][startY] = playerWhite[loc];
			}
			else{
				playerBlack[loc] = new Rook(BLACK);
				playerBlack[loc]->setGame(this);
				playerBlack[loc]->setLocation(startX,startY);
				theBoard[startX][startY] = playerBlack[loc];
			}
		}
		else if (promoteType== 'b'){
			if (currentPlayer == WHITE){
				playerWhite[loc] = new Bishop(WHITE);
				playerWhite[loc]->setGame(this);
				playerWhite[loc]->setLocation(startX,startY);
				theBoard[startX][startY] = playerWhite[loc];
			}
			else{
				playerBlack[loc] = new Bishop(BLACK);
				playerBlack[loc]->setGame(this);
				playerBlack[loc]->setLocation(startX,startY);
				theBoard[startX][startY] = playerBlack[loc];
			}
		}
		else if (promoteType == 'n'){
			if (currentPlayer == WHITE){
				playerWhite[loc] = new Knight(WHITE);
				playerWhite[loc]->setGame(this);
				playerWhite[loc]->setLocation(startX,startY);
				theBoard[startX][startY] = playerWhite[loc];
			}
			else{
				playerBlack[loc] = new Knight(BLACK);
				playerBlack[loc]->setGame(this);
				playerBlack[loc]->setLocation(startX,startY);
				theBoard[startX][startY] = playerBlack[loc];
			}
		}
	}

	//Check for castle
	if (theBoard[startX][startY]->getWorth() == KING  && (abs(startX - endX) == 2 || abs(startX - endX) == 3)){
		//If player is currently in check, returns false
		if (isCheck() == true) return false;
		
		//Variable to know which direction the king is moving
		int dir = 1;
		if (endX < startX) dir = -1;

		// Check is rook exists at required location and if it has moved
		if (dir == 1){
			if (isOccupied(7,startY) == false || theBoard[7][startY]->getWorth() != ROOK) return false;
			if (theBoard[7][startY]->getHasMoved() == true) return false;
		}
		else {
			if (isOccupied(0,startY) == false || theBoard[0][startY]->getWorth() != ROOK) return false;
			if (theBoard[0][startY]->getHasMoved() == true) return false;
		}


		//For all spaces the king will move through, checks if any of them would put the king in check
		for (int i = startX + dir; i != endX; i += dir){
			if (isCheckAfterMove(startX,startY,i,endY) == true) return false;
		}
		

		//Move the rook to the proper location here, and then let the normal movement algorithm move then King
		if (dir == 1){
			theBoard[endX - dir][endY] = theBoard[7][startY];	
			theBoard[7][startY] = NULL;
			theBoard[endX - dir][endY]->setLocation(endX - dir,endY);
			//Notifies of changes
			notify(7,startY,' ');
			notify(endX-dir,endY, theBoard[endX-dir][endY]->getName());
		}
		else{
			theBoard[endX - dir][endY] = theBoard[0][startY];	
			theBoard[0][startY] = NULL;
			theBoard[endX - dir][endY]->setLocation(endX - dir,endY);
			//Notifies of changes
			notify(7,startY,' ');
			notify(endX-dir,endY, theBoard[endX-dir][endY]->getName());
		}
	}	

	//For Kings and Rooks, if they have not moved before, setHasMoved to true;
	if (theBoard[startX][startY]->getWorth() == KING || theBoard[startX][startY]->getWorth() == ROOK){
		if (theBoard[startX][startY]->getHasMoved() == false) theBoard[startX][startY]->setHasMoved(true);
	}


	if (isOccupied(endX,endY) == true) theBoard[endX][endY]->setLocation(-1,-1);
	theBoard[endX][endY] = theBoard[startX][startY];	
	theBoard[startX][startY] = NULL;
	theBoard[endX][endY]->setLocation(endX,endY);

	//Notifies of changes
	notify(startX,startY,' ');
	notify(endX,endY, theBoard[endX][endY]->getName());

}

void Game::setCurrentPlayer(int player){
	currentPlayer = player;
}

int Game::getCurrentPlayer(){
	return currentPlayer;
}

void Game::init(){
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



void Game::setNotification(GameNotification* input){
	notifications = input;
}

void Game::addPiece(int x, int y, char piece){
	int player = WHITE;
	if (piece < 'A') player = BLACK;
	// Variable to store what location to put the piece in the Pieces array
	int location = -1;
	for (int i = 0; i < 16; i++){
		if (player == BLACK){
			if (playerBlack[i] == NULL){
				location = i;
				break;
			}
		}
		else{
			if (playerWhite[i] == NULL){
				location = i;
				break;
			}
		}
	}


	// If there are already 16 pieces on the board
	if (location == -1){
		cout << "Too many pieces on the board, remove some before trying to add more!" << endl;
		return;
	}


	int charDiff = 0;
	if (piece > 'A') charDiff = 'A' - 'a';

	Piece* newPiece;

	// If location is already occupied remove it and change co-ordinates
	if (isOccupied(x,y)){
		theBoard[x][y]->setLocation(-1,-1);
		theBoard[x][y] = NULL;
	}

	if (piece == 'k' + charDiff){
		newPiece = new King(player);
	}
	else if (piece == 'q' + charDiff){
		newPiece = new Queen(player);
	}
	else if (piece == 'r' + charDiff){
		newPiece = new Rook(player);
	}
	else if (piece == 'b' + charDiff){
		newPiece = new Bishop(player);
	}
	else if (piece == 'n' + charDiff){
		newPiece = new Knight(player);
	}
	else if (piece == 'p' + charDiff){
		newPiece = new Pawn(player);
	}

	if (player == BLACK){
		playerBlack[location] = newPiece;
	}
	else playerWhite[location] = newPiece;

	newPiece->setLocation(x,y);
	newPiece->setGame(this);
	theBoard[x][y] = newPiece;

}

void Game::removePiece(int x, int y, char piece){
	int player = WHITE;
	if (piece < 'A') player = BLACK;
	for (int i = 0; i < 16; i++){
		if (player == BLACK){
			if (playerBlack[i]->getX() == x && 
				playerBlack[i]->getY() == y && 
				playerBlack[i]->getName() == piece){
				delete playerBlack[i];
				playerBlack[i] = NULL;
				return;
			}
		}
		else{
			if (playerWhite[i]->getX() == x && 
				playerWhite[i]->getY() == y && 
				playerWhite[i]->getName() == piece){
				delete playerWhite[i];
				playerWhite[i] = NULL;
				return;
			}
		}
	}
}

bool Game::validBoard(){

	//Checks if either player is in Check
	if (isCheck(WHITE) || isCheck(BLACK)){
		cout << "A king is in Check. Unable to leave setup mode" << endl;
		return false;
	}
		// Checks if a pawn is in the top or bottom row
	for (int y = 0; y == 0 || y == 7; y+= 7){
		for (int x = 0; x < 8; x++){
			if (isOccupied(x,y) && theBoard[x][y]->getWorth() == PAWN){
				cout << "A pawn is in an invalid position. Unable to leave setup mode" << endl;
				return false;
			}
		}
	}
		//Check that there are exactly one white king and one black king
	int whiteKing = 0;
	int blackKing = 0;
	for (int x = 0; x < 8; x++){
		for (int y = 0; y < 8; y++){
			if (isOccupied(x,y)){
				if (theBoard[x][y]->getName() == 'k') ++whiteKing;
				else if (theBoard[x][y]->getName() == 'K') ++blackKing;
			}
		}
	}
		if (whiteKing != 1 || blackKing != 1){
		cout << "Invalid number of Kings. Unable to leave setup mode" << endl;
		return false;
	}
	return true;
}
