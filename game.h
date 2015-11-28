#ifndef GAME_H
#define GAME_H

const int WHITE = 1;
const int BLACK = -1;

class Piece;
class Cell;

class GameNotification {
  public:
    virtual void notify(int row, int column, char piece) = 0;
};

class Game {
	Piece** theBoard;
	Piece* playerWhite[16];
	Piece* playerBlack[16];
	GameNotification* notifications;
	int p1Score;
	int p2Score;
	bool whiteCastle;
	bool blackCastle;
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
	void setup();
	bool makeMove(int startX, int startY, int endX, int endY);
};

#endif
