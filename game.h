#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "pawn.h"


const int WHITE = 1;
const int BLACK = -1;
const int KING = -1;
const int QUEEN = 900;
const int ROOK = 500;
const int BISHOP = 305;
const int KNIGHT = 300;
const int PAWN = 100;

class Piece;
class Cell;

class GameNotification {
  public:
    virtual void notify(int row, int column, char piece) = 0;
};

class Game{
	Piece*** theBoard;
	Piece** playerWhite;
	Piece** playerBlack;
	GameNotification* notifications;
	int whiteScore;
	int blackScore;
	int currentPlayer;
	//Type of character to promote to
	void clearGame();
	

public:
	void notify(int x, int y, char c);// What will the parameters for this be
	bool hasWon();
	//Returns if current player is in Check
	bool isCheck(int player);
	bool isCheck();
	//Check is other player is in a Checkmate scenario
	bool isCheckmate();
	bool isStalemate();
	bool isOccupied(int x, int y);
	bool isValidMove(int startX, int startY, int endX, int endY);
	bool isPossibleMove(int startX, int startY, int endX, int endY); // returns true if move is possible based on the given board
	bool isCheckAfterMove(int startX, int startY, int endX, int endY, int player);
	bool isCheckAfterMove(int startX, int startY, int endX, int endY);
	void setCurrentPlayer(int player);
	int getCurrentPlayer();
	void init();
	bool makeMove(int startX, int startY, int endX, int endY, char promoteType = ' ', bool checkForCheck = true);
	void setNotification(GameNotification* input);
	void addPiece(int x, int y, char newPiece);
	void removePiece(int x, int y);
	bool validBoard();
	Game();
	~Game();
};

#endif
