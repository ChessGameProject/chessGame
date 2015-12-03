#include <cstdlib>

string AILevel1{}{

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
							//Return the output somehow

						}

						else ++counter;
					}
				}
			}
		}
	}



}