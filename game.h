#ifndef GAME_H
#define GAME_H

class Piece;
class Cell;

class Game{
	Cell** theBoard;
	Piece* playerWhite[16];
	Piece* playerBlack[16];
	GameNotifications* notifications;
	int p1Score;
	int p2Score;
	void clearGame();


public:
	void notify();// What will the parameters for this be?
	bool isWon();
	bool isCheck();
	bool isValidMove(int x1, int y1, int x2, int y2);
	bool setup();
	bool makeMove(int x1, int y1, int x2, int y2);


};

#endif
