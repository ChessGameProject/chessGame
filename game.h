#ifndef GAME_H
#define GAME_H

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
	Piece** theBoard[8][8];
	Piece* playerWhite[25];
	Piece* playerBlack[25];
	GameNotification* notifications;
	int p1Score;
	int p2Score;
	int currentPlayer;
	//Type of character to promote to
	void clearGame();
	Game();
	~Game();


public:
	void notify();// What will the parameters for this be?
	bool hasWon();
	//Returns if current player is in Check
	bool isCheck(int player = getCurrentPlayer());
	//Check is other player is in a Checkmate scenario
	bool isCheckmate();
	bool isStalemate();
	bool isOccupied(int x, int y);
	bool isValidMove(int startX, int startY, int endX, int endY);
	bool isPossibleMove(int startX, int startY, int endX, int endY); // returns true if move is possible based on the given board
	bool isCheckAfterMove(int startX, int startY, int endX, int endY, int player = getCurrentPlayer());
	void setCurrentPlayer(int player);
	int getCurrentPlayer();
	void initalSetup();
	void setup();
	bool makeMove(int startX, int startY, int endX, int endY, char promoteType = '', bool checkForCheck = true);


};

#endif
