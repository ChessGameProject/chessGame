#include <cstdlib>
#include <sstream>

string AILevel1(){

	//Finds how many valid moves are possible
	int numOfValidMoves = 0;

	Piece* currentPiece;
	for (int i = 0; i < 25; i++){	

		//Depending on the Player, determines which array to look in
		if ( player == BLACK ) currentPiece = playerBlack[i];
		else currentPiece = playerWhite[i];

		//If there is no piece at that location, continues
		if (currentPiece == NULL) continue;

		//Goes through all possible locations on the board and see if there is a move that would result in
		//The king not being in Check
		for (int x = 0; x < 8; x++){
			for (int y = 0; y < 8; y++){
				bool valid = isValidMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
				if ( valid ){	  
					bool isInCheck = isCheckAfterMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
					if ( !isInCheck ) {
						++numOfValidMoves;
					}
				}
			}
		}
	}

	int outputMove =  rand() % numOfValidMoves;

	int counter = 0;

	//Goes through all valid moves until it gets to the random one
	for (int i = 0; i < 25; i++){	

		//Depending on the Player, determines which array to look in
		if ( player == BLACK ) currentPiece = playerBlack[i];
		else currentPiece = playerWhite[i];

		//If there is no piece at that location, continues
		if (currentPiece == NULL) continue;

		//Goes through all possible locations on the board and see if there is a move that would result in
		//The king not being in Check
		for (int x = 0; x < 8; x++){
			for (int y = 0; y < 8; y++){
				bool valid = isValidMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
				if ( valid ){	  
					bool isInCheck = isCheckAfterMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
					if ( !isInCheck ) {
						if (counter == outputMove){
							return outputFormat(currentPiece->getX(),currentPiece->getY(),x,y);
						}

						else ++counter;
					}
				}
			}
		}
	}
}


//Prefers moves with captures and checks if possible
string AILevel2(){

	//Finds how many valid moves are possible
	int numOfValidMoves = 0;;
	int numOfCheckMoves = 0;
	int numOfCaptureMoves = 0;
	int highestCapture = 0;
	int targetXstart = -1;
	int targetYstart = -1;
	int targetXend = -1;
	int targetYend = -1;

	Piece* currentPiece;
	for (int i = 0; i < 25; i++){	

		//Depending on the Player, determines which array to look in
		if ( otherPlayer == BLACK ) currentPiece = playerBlack[i];
		else currentPiece = playerWhite[i];

		//If there is no piece at that location, continues
		if (currentPiece == NULL) continue;

		//Goes through all possible locations on the board and see if there is a move that would result in
		//The king not being in Check
		for (int x = 0; x < 8; x++){
			for (int y = 0; y < 8; y++){
				bool valid = isValidMove(currentPiece->getX(),currentPiece->getY(),x,y);
				if ( valid ){
					bool captureMove = false;
					if (currentPiece->getPlayer() != theBoard[x][y]->getPlayer()) captureMove = true;

					if (captureMove) {
						++numOfCaptureMoves;
						if (theBoard[x][y]->getValue() > highestCapture) {
							targetXstart = currentPiece->getX();
							targetYstart = currentPiece->getY();
							targetXend = x;
							targetYend = y;
						}
					}

					bool selfIisInCheck = isCheckAfterMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
					if ( !selfIsInCheck ) {
						++numOfValidMoves;
						bool otherIsInCheck = isCheckAfterMove(currentPiece->getX(),currentPiece->getY(),x,y, otherPlayer);
						if (otherIsInCheck) ++numOfCheckMoves;
						if (otherIsInCheck && captureMove) {
							++numOfCheckAndCaptureMoves;
							if (theBoard[x][y]->getValue() > highestCapture - 10) {
								targetXstart = currentPiece->getX();
								targetYstart = currentPiece->getY();
								targetXend = x;
								targetYend = y;
							}
						}
					}
				}
			}
		}
	}

	//If it couldn't find any capture or check moves, return a random move
	if (targetX == numOfCheckMoves && targetY == numOfCaptureMoves) return AILevel1();

	else return outputFormat(targetXstart,targetYstart,targetXend,targetYend);	
}






string outputFormat(int startX, int startY, int endX, int endY){
	string output = "move "
	ostringstream = ss;
	char temp = startX;
	ss << temp  + 'a';
	output = output + ss.str();
	ss << 8 - startY;
	output = output + ss.str() + " ";

	char temp = endX;
	ss << temp  + 'a';
	output = output + ss.str();
	ss << 8 - endY;
	output = output + ss.str() + " ";

	return output;
}