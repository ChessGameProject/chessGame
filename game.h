#ifndef GAME_H
#define GAME_H

const int WHITE = 1;
const int BLACK = 2;

class Piece;
class Cell;

class GameNotification {
  public:
    virtual void notify(int row, int column, char piece) = 0;
};

class Game{
	Piece** theBoard[8][8];
	Piece* playerWhite[16];
	Piece* playerBlack[16];
	GameNotification* notifications;
	int p1Score;
	int p2Score;
	int currentPlayer;
	bool whiteCastle;
	bool blackCastle;
	//If true, the given move is a pawn promotion
	bool pawnPromote;
	//Type of character to promote to
	char promoteType;
	void clearGame();
	Game();
	~Game();


public:
	void notify();// What will the parameters for this be?
	bool isWon();
	bool isCheck(int player);
	bool isCheckmate(int player);
	bool isOccupied(int x, int y);
	bool isValidMove(int startX, int startY, int endX, int endY);
	bool isPossibleMove(int startX, int startY, int endX, int endY); // returns true if move is possible based on the given board
	int getCurrentPlayer();
	bool getPawnPromote();
	char getPromoteType();
	void setPawnPromote(bool promote);
	void setPromoteType(char type)
	void setup();
	bool makeMove(int startX, int startY, int endX, int endY);


};

#endif
