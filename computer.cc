#include "computer.h"
#include <cstdlib>
#include <sstream>

using namespace std;

Computer::Computer(Controller *c, Game *g, bool automatic, int i, int player) : Player(c) {
	level = i;
	game = g;
	this->automatic = automatic;
	this->player = player;
}

string Computer::getNextMove(){
	string cmd;
	if (automatic == false) {
		while (cin >> cmd) {
			if (cmd == "move") {
				if (level == 1) return AILevel1();
				if (level == 2) return AILevel2();
				else return AILevel2();
			} else if (cmd == "resign") {
				return cmd;
			} else {
				cout << "Try a different command" << endl;
			}
		}
		if (cin.eof()) return "quit";
	} else {
		if (level == 1) return AILevel1();
		if (level == 2) return AILevel2();
		else return AILevel2();
	}
	
	return "none";
}



string Computer::AILevel1(){

	#ifdef DEBUG3
		cout << "player: " << player << endl;
	#endif

	//Finds how many valid moves are possible
	int numOfValidMoves = 0;

	Piece* currentPiece;
	for (int i = 0; i < 25; i++){	

		//Depending on the Player, determines which array to look in
		if ( player == BLACK ) currentPiece = game->getPlayerBlack(i);
		else currentPiece = game->getPlayerWhite(i);

		//If there is no piece at that location, continues
		if (currentPiece == NULL || currentPiece->getX() == -1) continue;

		//Goes through all possible locations on the board and see if there is a move that would result in
		//The king not being in Check
		for (int x = 0; x < 8; x++){
			for (int y = 0; y < 8; y++){
				bool valid = game->isValidMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
				if ( valid ){	  
					bool isInCheck = game->isCheckAfterMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
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
		if ( player == BLACK ) currentPiece = game->getPlayerBlack(i);
		else currentPiece = game->getPlayerWhite(i);

		//If there is no piece at that location, continues
		if (currentPiece == NULL) continue;

		//Goes through all possible locations on the board and see if there is a move that would result in
		//The king not being in Check
		for (int x = 0; x < 8; x++){
			for (int y = 0; y < 8; y++){
				bool valid = game->isValidMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
				if ( valid ){	  
					bool isInCheck = game->isCheckAfterMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
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
	return "ERROR";
}


//Prefers moves with captures and checks if possible
string Computer::AILevel2(){

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
		if ( player == BLACK ) currentPiece = game->getPlayerBlack(i);
		else currentPiece = game->getPlayerWhite(i);

		//If there is no piece at that location, continues
		if (currentPiece == NULL || currentPiece->getX() == -1) continue;

		//Goes through all possible locations on the board and see if there is a move that would result in
		//The king not being in Check
		for (int x = 0; x < 8; x++){
			for (int y = 0; y < 8; y++){
				bool valid = game->isOccupied(x,y) && game->isValidMove(currentPiece->getX(),currentPiece->getY(),x,y,player);
				if ( valid ){
					bool captureMove = false;
					if (currentPiece->getPlayer() != game->getBoardLocation(x,y)->getPlayer()) captureMove = true;

					if (captureMove) {
						++numOfCaptureMoves;
						if (game->getBoardLocation(x,y)->getWorth() > highestCapture) {
							targetXstart = currentPiece->getX();
							targetYstart = currentPiece->getY();
							targetXend = x;
							targetYend = y;
						}
					}

					bool selfIsInCheck = game->isCheckAfterMove(currentPiece->getX(),currentPiece->getY(),x,y, player);
					if ( !selfIsInCheck ) {
						++numOfValidMoves;
						bool otherIsInCheck = game->isCheckAfterMove(currentPiece->getX(),currentPiece->getY(),x,y, player*(-1) );
						if (otherIsInCheck) ++numOfCheckMoves;
						if (otherIsInCheck && captureMove) {
							if (game->getBoardLocation(x,y)->getWorth() > highestCapture - 10) {
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
	if (targetXend == -1) {
		#ifdef DEBUG3
		cout << "	Didn't find any good moves :( " << endl;
		#endif
		return AILevel1();
	}

	else return outputFormat(targetXstart,targetYstart,targetXend,targetYend);	
}






string Computer::outputFormat(int startX, int startY, int endX, int endY){
	stringstream ss1;
	stringstream ss2;
	ss1 << startX << 8 - startY;
	ss2 << endX << 8 - endY;
	string temp1 = ss1.str();
	string temp2 = ss2.str();
	temp1[0] = temp1[0] +'a' - '0';
	temp2[0] = temp2[0] +'a' - '0';
	string output = "move " + temp1 + " " + temp2;
	
	return output;
}






