#include "game.h"
#include "piece.h"
#include <iostream>

using namespace std;
/*
TO DO:
- En Passant
- Stalemate with 3 move repetition
*/

Game::Game(){
	//Constructs Array of Piece** for theBoard to place the 2D array of Piece*
	theBoard = new Piece**[8];

	//Sets all pieces in Board to NULL
	for(int i = 0; i < 8; i++){
		theBoard[i] = new Piece*[8];
		for (int j = 0; j < 8; j++){
			theBoard[i][j] = NULL;
		}
	}

	//Allocates arrays to store Pieces for each player
	playerWhite = new Piece*[25];
	playerBlack = new Piece*[25];

	//Sets all values in Piece array to NULL
	for (int i = 0; i < 25; i++){
		playerWhite[i] = NULL;
		playerBlack[i] = NULL;
	}
	
	possibleEP = false;
	enPassantX = -1;
	enPassantY = -1;
	whiteScore = 0;
	blackScore = 0;

	//By default sets player to go first to be WHITE
	currentPlayer = WHITE;
}

Game::~Game(){
	clearGame(false);
}

void Game::notify(int x, int y, char ch){
	notifications->notify(x,y,ch);
}

void Game::notifyTwo(int x, int y, char ch, int x2, int y2, char ch2){
	notifications->notifyTwo(x,y,ch, x2,y2,ch2);
}

// Deletes old pieces and board and creates a new blank one (if restart is true)
// restart defaults to true
void Game::clearGame(bool restart){
	//
	// Clear game board
	//
	// If there is a Piece in the Piece array, delete the Piece
	for ( int i = 0; i < 25; i++ ) {
		if (playerWhite[i] != NULL) delete playerWhite[i];
		if (playerBlack[i] != NULL) delete playerBlack[i];
	}

	//delete the Piece arrays
	delete [] playerWhite;
	delete [] playerBlack;

	//Since 2D array, delete both dimensions on the array
	for (int i = 0; i < 8; i++ ) {
		delete [] theBoard[i];
	}
	delete [] theBoard;

	// 
	// Setup new board
	//
	if (restart) {
		// Create new board
		theBoard = new Piece**[8];
		//Sets all pieces in Board to NULL
		for(int i = 0; i < 8; i++){
			theBoard[i] = new Piece*[8];
			for (int j = 0; j < 8; j++){
				theBoard[i][j] = NULL;
			}
		}

		playerWhite = new Piece*[25];
		playerBlack = new Piece*[25];

		for (int i = 0; i < 25; i++){
			playerWhite[i] = NULL;
			playerBlack[i] = NULL;
		}
			
		if ((whiteScore + blackScore)%2 == 0) currentPlayer = WHITE;
		else currentPlayer = BLACK;
	}
	
}

bool Game::isCheckAfterMove(int startX, int startY, int endX, int endY){
	return isCheckAfterMove(startX,startY, endX, endY, currentPlayer);
}

bool Game::isCheckAfterMove(int startX, int startY, int endX, int endY, int player){
	#ifdef DEBUG
	  	cout << "(isCheckAfterMove)" << endl;
	#endif
	//Temp piece to put back into the Board after temp move is made
	Piece* temp = theBoard[endX][endY];
	
	//Makes the move and then see if player is in Check after the move
	unrestrictedMakeMove(startX,startY,endX,endY);
	bool output = false;
	if (isCheck(player) == true) output = true;

	//Puts the pieces back
	unrestrictedMakeMove(endX,endY,startX,startY);
	theBoard[endX][endY] = temp;
	if( isOccupied(endX,endY) ) theBoard[endX][endY]->setLocation(endX,endY);

	// So we don't lose the Piece stored in temp
	temp = NULL;
	#ifdef DEBUG
	  	cout << "__isCheckAfterMove__" << endl;
	#endif
	return output;
}

void Game::unrestrictedMakeMove(int startX, int startY, int endX, int endY) {
  #ifdef DEBUG
  	cout << "    (unrestrictedMakeMove(" << startX << "," << startY << " ";
  	cout << endX << "," << endY << "))" << endl;
  #endif
	
	//If the move eats a Piece, set that eaten piece to have a null location
  	if (isOccupied(endX,endY)) theBoard[endX][endY]->setLocation(-1,-1);

  	//Move Piece to the new location
	theBoard[endX][endY] = theBoard[startX][startY];
	theBoard[startX][startY] = NULL;
	theBoard[endX][endY]->setLocation(endX,endY);
}

bool Game::isValidMove(int startX, int startY, int endX, int endY){
	return isValidMove(startX, startY, endX, endY, currentPlayer);
}

bool Game::isValidMove(int startX, int startY, int endX, int endY, int player){
	#ifdef DEBUG2
  	cout << "    (isValidMove(" << startX << "," << startY << " ";
  	cout << endX << "," << endY << "))" << endl;
  	#endif

	//Checks if input is within the bounds of the board
	if (startX > 7 || startX < 0 || startY > 7 || startY < 0 || endX < 0 || endX > 7 || endY > 7 || endY < 0) return false;
	if (startX == endX && startY == endY) {
		#ifdef DEBUG2
  		cout << "    (isValidMove(" << startX << "," << startY << " ";
  		cout << endX << "," << endY << ")) is false for invalid board location" << endl;
  		#endif
		return false;
	}

	//If there is no piece at the specified location, returns false
	if (isOccupied(startX,startY) == false) {
		#ifdef DEBUG2
  		cout << "    (isValidMove(" << startX << "," << startY << " ";
  		cout << endX << "," << endY << ")) is false because there is not piece there to move!" << endl;
  	#endif
		return false;
	}

	//Check that the Piece belongs to the right player!
	if (theBoard[startX][startY]->getPlayer() != player) {
		#ifdef DEBUG2
  		cout << "    (isValidMove(" << startX << "," << startY << " ";
  		cout << endX << "," << endY << ")) is false because that piece doesn't belong to you!" << endl;
  	#endif
		return false;
	}

	//Checks if piece it is capturing is on the correct team
	if (isOccupied(endX,endY) && theBoard[endX][endY]->getPlayer() == player) {
		return false;
	}



	//Check is Move is invalid from the Piece class
	if (theBoard[startX][startY]->isMoveValid(endX,endY) == false) {
		#ifdef DEBUG2
  		cout << "    (isValidMove(" << startX << "," << startY << " ";
  		cout << endX << "," << endY << ")) is false because move isMoveValid() is false" << endl;
  	#endif
		return false;
	}

	
	#ifdef DEBUG2
	cout << "    (isValidMove(" << startX << "," << startY << " ";
	cout << endX << "," << endY << ")) is true" << endl;
	#endif
	return true;


	//Check for en passant

}

bool Game::isOccupied(int x, int y){
	#ifdef DEBUG2
  	cout << "    (isOccupied(" << x << "," << y << "))";
  #endif

  	//Checks if input is within the bounds of the board
	if (x < 0 || y < 0 || x > 7 || y > 7) return false;

	if (theBoard[x][y] == NULL) {
		#ifdef DEBUG2
			cout << " is false" << endl;
		#endif
		return false;
	}
	else {
		#ifdef DEBUG2
			cout << " is true" << endl;
		#endif
		return true;
	}
}

bool Game::isCheckmate(){
	#ifdef DEBUG
  		cout << "    (isCheckmate)" << endl;
  	#endif

  	//Sets the player to be the other player
	int player = currentPlayer*(-1);

	//Finds the Location the the King the the array of pieces and create pointer to it
	Piece *king;
	if (currentPlayer == WHITE){
		#ifdef DEBUG
  			cout << "        - finding BLACK king" << endl;
 	 	#endif

  		//Goes through each Black piece and to find the King
		for (int i = 0; i < 25; i++){
			if ( (playerBlack[i] != NULL) && (playerBlack[i]->getWorth() == KING) ){
				king = playerBlack[i];
				#ifdef DEBUG
  					cout << "        - king found (BLACK) at " << i << endl;
  				#endif
				break;
			}
		}
	}
	else{
		#ifdef DEBUG
  			cout << "        - finding WHITE king" << endl;
  		#endif
		for (int i = 0; i < 25; i++){
			if ( (playerWhite[i] != NULL) && (playerWhite[i]->getWorth() == KING) ){
				king = playerWhite[i];
				#ifdef DEBUG
	  				cout << "        - king found (WHITE) at " << i << endl;
	  			#endif
				break;
			}
		}
	}


	//For all possible moves around the king, it checks if after moving the king there would result in a Check position
	for (int x = -1; x <= 1; x++){
		for (int y = -1; y <= 1; y++){
			#ifdef DEBUG
  			cout << "        - Check king's move to ("<< king->getX() + x <<","<< king->getY() + y <<")" << endl;
  			#endif

  			//Checks if the proposed move is valid
			bool valid = isValidMove(king->getX(),king->getY(),king->getX() + x,king->getY() + y);
			if ( !valid ){
  				continue;
			}

			//Checks if the proposed move would leave the king in Check
			bool isInCheck = isCheckAfterMove(king->getX(),king->getY(),king->getX() + x,king->getY() + y, player);
			if ( !isInCheck ) {
				#ifdef DEBUG1
  					cout << "      __isCheckmate (false) because (" << king->getX() << ",";
  					cout << king->getY() << ") to (" << king->getX() + x << "," << king->getY() + y << ") is a valid move" << endl;
  				#endif

				#ifdef DEBUG
  					cout << "      __isCheckmate (false) because not check after move" << endl;
  				#endif

				return false;
			}
		}
	}


	//Checks if there is a space any piece could move to that would create a non-check position
	Piece* currentPiece;
	for (int i = 0; i < 25; i++){	

		//Depending on the Player, determines which array to look in
		if ( player == BLACK ) currentPiece = playerBlack[i];
		else currentPiece = playerWhite[i];

		//If there is no piece at that location, continues
		if (currentPiece == NULL || currentPiece->getWorth() == KING) continue;

		//Goes through all possible locations on the board and see if there is a move that would result in
		//The king not being in Check
		for (int x = 0; x < 8; x++){
			for (int y = 0; y < 8; y++){
				bool valid = isValidMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
				if ( valid ){	  
					bool isInCheck = isCheckAfterMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
					if ( !isInCheck ) {
						#ifdef DEBUG1
						cout << "      __isCheckmate (false) because (" << currentPiece->getX() << "," << currentPiece->getY() << ") to (" << x << ", " << y << ")";
						cout << " with " << currentPiece->getName() << " for player " << player  << " is a valid move"<< endl;
						#endif
						return false;
					}
				}
			}
		}
	}


	//If all checks pass, the King must then be in Checkmate
	#ifdef DEBUG
  	cout << "      __isCheckmate (true)__" << endl;
  	#endif
	return true;
}

bool Game::isStalemate(){

	if (currentPlayer == BLACK){
		//goes through each piece and tries to find a valid move for any piece
		for (int i = 0; i < 24; i++){
			if (playerWhite[i] == NULL) continue;
			for(int x = 0; x < 8; x++){
				for(int y = 0; y < 8; y++){
					//If it can find a valid move for the current player, returns false since it is not a stalemate
					if (isValidMove(playerWhite[i]->getX(),playerWhite[i]->getY(),x,y,WHITE) == true) {
						if ( isCheckAfterMove(playerWhite[i]->getX(),playerWhite[i]->getY(),x,y,WHITE) ==  false) return false;
					}
				}
			}
		}
	}
	else{
		for (int i = 0; i < 24; i++){
			if (playerBlack[i] == NULL) continue;
			for(int x = 0; x < 8; x++){
				for(int y = 0; y < 8; y++){
					if (isValidMove(playerBlack[i]->getX(),playerBlack[i]->getY(),x,y,BLACK) == true) {
						if ( isCheckAfterMove(playerBlack[i]->getX(),playerBlack[i]->getY(),x,y,BLACK) == false) return false;
					}
				}
			}
		}
	}
	return true;
}

bool Game::hasWon(){
	//Checks if opposing player is in Check. If not, impossible to win game
	if ( !isCheck( currentPlayer*(-1) )) return false;

	// Determines if opposition is in Checkmate
	bool output = isCheckmate();

	//If opposition is in Checkmate, then increment the score accordingly
	if (output){
		if (currentPlayer == WHITE) ++whiteScore;
		else ++blackScore;
	}
	return output;
}

bool Game::isCheck(int player){
	#ifdef DEBUG
  	cout << "(isCheck) " << player << endl;
  #endif
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
					#ifdef DEBUG
  					cout << "__isCheck (true)__ for piece " << playerBlack[i]->getName()<< endl;
  				#endif
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
					#ifdef DEBUG
  					cout << "__isCheck (true)__ for piece " << playerWhite[i]->getName()<< endl;
  				#endif
					return true;
				}
			}
		}
	}
	#ifdef DEBUG
  	cout << "__isCheck (false)__"<< endl;
  #endif
	return false;
}

bool Game::isCheck(){
	return isCheck(currentPlayer);
}

bool Game::makeMove(int startX, int startY, int endX, int endY, char promoteType, bool checkForCheck){
	#ifdef DEBUG
  		cout << "(makeMove)" << endl;
  	#endif

  // Check the move is valid for the given piece
	if (isValidMove(startX,startY,endX,endY) == false) return false;

	//Checks to see if Piece is trying to capture another piece of its own team
	if ( isOccupied(endX, endY) ) {
		for (int i = 0; i < 25; i++){
			if (currentPlayer == WHITE){
				if(playerWhite[i] == theBoard[endX][endY]) return false;
			}
			else{
				if(playerBlack[i] == theBoard[endX][endY]) return false;
			}
		}
	}
	

	//Check for Check
	if (checkForCheck == true){
		if (isCheckAfterMove(startX,startY,endX,endY) == true) return false;
	}

	//Checks if Pawn is moving to a promotion square and there is no promotion type
	//If no promotion type and one is needed, set promotion typ to Queen
	if ( (theBoard[startX][startY]->getWorth() == PAWN ) && (endY == 0 || endY == 7) && ( promoteType == ' ' ) ) {
		promoteType = 'q';
	}

	//Checks for Pawn Promotion,
	if (promoteType != ' '){
		#ifdef DEBUG
  		cout << "    (pawnPromoCheck)" << endl;
  		#endif

		//Checks that the piece is a pawn moving to the end row
		if (theBoard[startX][startY]->getWorth() != PAWN) return false;
		if (currentPlayer == WHITE && endY != 0) return false;
		if (currentPlayer == BLACK && endY != 7) return false;



		// Check if character is correct Case
		if (promoteType < 'Z') promoteType = promoteType + 'A' - 'a';

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

		Piece * temp;

		if (promoteType == 'q'){
			temp = new Queen(currentPlayer);
		}
		else if (promoteType == 'r'){
			temp = new Rook(currentPlayer);
		}
		else if (promoteType== 'b'){
			temp = new Bishop(currentPlayer);
		}
		else if (promoteType == 'n'){
			temp = new Knight(currentPlayer);
		}
		else {
			#ifdef DEBUG
		  		cout << "	__Invalid PromoteType: " << promoteType << endl;
		  	#endif
			return false;
		}

		if (currentPlayer == WHITE){
			playerWhite[loc] = temp;
			playerWhite[loc]->setGame(this);
			playerWhite[loc]->setLocation(endX,endY);
			theBoard[endX][endY] = playerWhite[loc];
			theBoard[startX][startY]->setLocation(-1,-1);
			theBoard[startX][startY] = NULL;

			notifyTwo(startX,startY,'\0',endX,endY,temp->getName());

			return true;
		}
		else{
			playerBlack[loc] = temp;	
			playerBlack[loc]->setGame(this);
			playerBlack[loc]->setLocation(endX,endY);
			theBoard[endX][endY] = playerBlack[loc];
			theBoard[startX][startY]->setLocation(-1,-1);
			theBoard[startX][startY] = NULL;

			notifyTwo(startX,startY,'\0',endX,endY,temp->getName());

			return true;
		}
	}

	//Check for castle
	if (theBoard[startX][startY]->getWorth() == KING  && (abs(startX - endX) == 2 || abs(startX - endX) == 3)){
		#ifdef DEBUG
		 	cout << "    (checkCastle)" << endl;
		#endif
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
			notify(7,startY,'\0');
			notify(endX-dir,endY, theBoard[endX-dir][endY]->getName());
		}
		else{
			theBoard[endX - dir][endY] = theBoard[0][startY];	
			theBoard[0][startY] = NULL;
			theBoard[endX - dir][endY]->setLocation(endX - dir,endY);
			//Notifies of changes
			notify(0,startY,'\0');
			notify(endX-dir,endY, theBoard[endX-dir][endY]->getName());
		}
	}	

	//Handles Enpassant

	//Checks if Move would make the next move en passant possible
	if ( (endX - startX) == 0 && ( abs(endY - startY) ) == 2 && theBoard[startX][startY]->getWorth() == PAWN){
		if (endY > startY) {
			setEnPassant(endX, endY - 1 );
		}
		else {
			setEnPassant( endX, endY + 1);
		}
	}
	//Checks if current move would be a possible enPassant Move
	else if (enPassantPossible(endX,endY) && theBoard[startX][startY]->getWorth() == PAWN){
		int dir = 1;
		if (endY > startY) dir = -1;
		theBoard[endX][endY + dir]->setLocation(-1,-1);
		notify(endX,endY + dir,'\0');
		clearEnPassant();
	}
	else clearEnPassant();

	#ifdef DEBUG
  		cout << "    (setHasMoved)" << endl;
  	#endif
	//if piece has not moved before, setHasMoved to true;
	if (theBoard[startX][startY]->getHasMoved() == false) theBoard[startX][startY]->setHasMoved(true);


	if (isOccupied(endX,endY) == true) theBoard[endX][endY]->setLocation(-1,-1);
	theBoard[endX][endY] = theBoard[startX][startY];	
	theBoard[startX][startY] = NULL;
	theBoard[endX][endY]->setLocation(endX,endY);

	#ifdef DEBUG
  		cout << "    (notification time!)" << endl;
  	#endif
	//Notifies of changes only happens at the end of the process
  if (checkForCheck) {
  	// Update both the cell moved from and moved to
  	notifyTwo(endX, endY, theBoard[endX][endY]->getName(), 
  						startX, startY, '\0');
  }
	#ifdef DEBUG
  		cout << "__move made__" << endl;
  		cout << playerBlack[0]->getName() << endl;
  	#endif
	return true;

}

void Game::init(){
	// Clear board view
	for(int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			notify(i,j, '\0');
		}
	}

	//Sets initial location of Pawns
	for (int i = 0; i < 8; i++){
		playerWhite[i] = new Pawn(WHITE);
		playerWhite[i]->setGame(this);
		playerWhite[i]->setLocation(i,6);
		theBoard[i][6] = playerWhite[i];
		notify(i,6,'P');

		playerBlack[i] = new Pawn(BLACK);
		playerBlack[i]->setGame(this);
		playerBlack[i]->setLocation(i,1);
		theBoard[i][1] = playerBlack[i];
		notify(i,1,'p');
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

	// Harcode notifications
	// BLACK
	notify(0,0,'r');
	notify(1,0,'n');
	notify(2,0,'b');
	notify(3,0,'q');
	notify(4,0,'k');
	notify(5,0,'b');
	notify(6,0,'n');
	notify(7,0,'r');
	// WHITE
	notify(0,7,'R');
	notify(1,7,'N');
	notify(2,7,'B');
	notify(3,7,'Q');
	notify(4,7,'K');
	notify(5,7,'B');
	notify(6,7,'N');
	notify(7,7,'R');
}



void Game::setNotification(GameNotification* input){
	notifications = input;
}

void Game::addPiece(int x, int y, char piece){
	int player = WHITE;
	if ( (piece < 'z') && (piece > 'a') ) player = BLACK;

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



	Piece* newPiece;

	// If location is already occupied remove it and change co-ordinates
	if (isOccupied(x,y)){
		theBoard[x][y]->setLocation(-1,-1);
		theBoard[x][y] = NULL;
	}

	//Creates new piece depending on the specified type
	if (piece == 'k' || piece == 'K'){
		newPiece = new King(player);
	}
	else if ( piece == 'q' || piece == 'Q' ){
		newPiece = new Queen(player);
	}
	else if (piece == 'r' || piece == 'R'){
		newPiece = new Rook(player);
	}
	else if (piece == 'b' || piece == 'B'){
		newPiece = new Bishop(player);
	}
	else if (piece == 'n' || piece == 'N'){
		newPiece = new Knight(player);
	}
	else if (piece == 'p' || piece == 'P'){
		newPiece = new Pawn(player);
	} else {
		// No piece
		#ifdef DEBUG
		cout << "No Piece could be created for type " << piece << endl;
		#endif
		return;
	}

	if (player == BLACK){
		playerBlack[location] = newPiece;
		#ifdef DEBUG
		cout << "playerBlack[" << location << "] has value " << playerBlack[location]->getWorth() <<endl;
		#endif
	}
	else {
		playerWhite[location] = newPiece;
		#ifdef DEBUG
		cout << "playerWhite[" << location << "] has value " << playerWhite[location]->getWorth() <<endl;
		#endif
	}

	newPiece->setLocation(x,y);
	newPiece->setGame(this);
	theBoard[x][y] = newPiece;
	notifications->notify(x,y,newPiece->getName());


	// So we don't lose the new piece
	newPiece = NULL;


	#ifdef DEBUG
		cout << "theBoard[" << x << "][" << y << "] has value " << theBoard[x][y]->getWorth() <<endl;
	#endif

}

void Game::removePiece(int x, int y){

	// If no piece exists at the location, don't do anything
	if (!isOccupied(x,y)) return;

	#ifdef DEBUG
		cout << "(removePiece)" <<endl;
	#endif

	int player = WHITE;
	char piece = theBoard[x][y]->getName();
	if ( (piece < 'z') && (piece > 'a') ) player = BLACK;


	//Goes through the Piece array to find the piece at the same location
	for (int i = 0; i < 16; i++){
		if (player == BLACK){
			if (playerBlack[i]->getX() == x && 
				playerBlack[i]->getY() == y) {
				delete playerBlack[i];
				playerBlack[i] = NULL;
				break;
			}
		}
		else{
			if (playerWhite[i]->getX() == x && 
				playerWhite[i]->getY() == y) {
				delete playerWhite[i];
				playerWhite[i] = NULL;
				break;
			}
		}
	}

	//notifies of changes
	notifications->notify(x,y,'\0');
}

bool Game::validBoard(){

	//Checks if either player is in Check
	if (isCheck(WHITE) || isCheck(BLACK)){
		cout << "A king is in Check. Unable to leave setup mode" << endl;
		return false;
	}
	// Checks that all pawna are in the top or bottom row
	for (int y = 0; y == 0 || y == 7; y+= 7){
		for (int x = 0; x < 8; x++){
			if (isOccupied(x,y) && theBoard[x][y]->getWorth() == PAWN){
				cout << "A pawn is in an invalid position. Unable to leave setup mode" << endl;
				return false;
			}
		}
	}
	
	//Checks that there are exactly one white king and one black king
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

	//If there are not one of each king, invalid number of Kings
	if (whiteKing != 1 || blackKing != 1){
		cout << "Invalid number of Kings. Unable to leave setup mode" << endl;
		return false;
	}
	return true;
}

bool Game::isPawnPromotion(int startX, int startY, int endX, int endY) const {
	// Check if starting position is a pawn and ending is in the endzone
	if ( (theBoard[startX][startY]->getWorth() == 100) && 
			 (endY == 0 || endY == 7) ) {
		return true;
	}
	return false;
}


bool Game::enPassantPossible(int x, int y){
	if ( possibleEP && enPassantX == x && enPassantY == y ) return true;
	else return false;
}

void Game::setEnPassant(int x, int y){
	possibleEP = true;
	enPassantX = x;
	enPassantY = y;
}

void Game::clearEnPassant(){
	possibleEP = false;
	enPassantX = -1;
	enPassantY = -1;
}

// Getters and Setters

void Game::setCurrentPlayer(int player){
	currentPlayer = player;
}

int Game::getCurrentPlayer(){
	return currentPlayer;
}

int Game::getWhiteScore() {
	return whiteScore;
}

int Game::getBlackScore() {
	return blackScore;
}

void Game::incrementWhiteScore() {
	whiteScore++;
}

void Game::incrementBlackScore() {
	blackScore++;
}

Piece* Game::getPlayerWhite(int location){
	return playerWhite[location];
}

Piece* Game::getPlayerBlack(int location){
	return playerBlack[location];
}

Piece* Game::getBoardLocation(int x, int y){
	return theBoard[x][y];
}

