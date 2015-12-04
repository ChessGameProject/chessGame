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
    virtual void notify(int x, int y, char ch) = 0;
    virtual void notifyTwo(int x, int y, char ch, int x2, int y2, char ch2) = 0;
};

class Game{
	Piece*** theBoard;
	Piece** playerWhite;
	Piece** playerBlack;
	GameNotification* notifications;
	int whiteScore;
	int blackScore;
	int currentPlayer;
	//Possible En Passant
	bool possibleEP;
	int enPassantX;
	int enPassantY;

public:
	Game(); // ctor
	~Game(); // dtor

	//Notifications
	void notify(int x, int y, char ch);
	void notifyTwo(int x, int y, char ch, int x2, int y2, char ch2);

	bool hasWon();

	//Reset the board and clear pieces
	void clearGame(bool restart = true);

	//Returns if current player is in Check
	bool isCheck();
	//Same as isCheck(), but sets which player to check if in Check
	bool isCheck(int player);

	//Checksis other player is in a Checkmate scenario
	bool isCheckmate();
	//Checks if Board is in Stalemate state
	bool isStalemate();

	//Checks is specified Board location is occupied by a Piece
	bool isOccupied(int x, int y);

	//Checks if moving from one location to another is a valid move
	bool isValidMove(int startX, int startY, int endX, int endY);
	bool isValidMove(int startX, int startY, int endX, int endY, int player);

	//Checks if after the given move, the player is in Check
	bool isCheckAfterMove(int startX, int startY, int endX, int endY, int player);
	bool isCheckAfterMove(int startX, int startY, int endX, int endY);

	//makes move from and to specified locations, whith validity Checks
	bool makeMove(int startX, int startY, int endX, int endY, char promoteType = ' ', bool checkForCheck = true);

	//Makes move with no restrictions
	void unrestrictedMakeMove(int startX, int startY, int endX, int endY);

	//Initializes Board to default position
	void init();

	//Adds Piece to the Board
	void addPiece(int x, int y, char newPiece);

	//removes Piece from the Board
	void removePiece(int x, int y);

	//Checks if the Board is in a valid state to leave setup mode
	bool validBoard();

	//Checks if enPassant is Possible with given Move
	bool enPassantPossible(int x, int y);
	void setEnPassant(int x, int y);
	void clearEnPassant();

	//Setters
	void setCurrentPlayer(int player);
	void setNotification(GameNotification* input);
	void incrementWhiteScore();
	void incrementBlackScore();

	//Getter
	int getCurrentPlayer();	
	int getWhiteScore();

	int getBlackScore();


	Piece* getPlayerWhite(int location);
	Piece* getPlayerBlack(int location);
	Piece* getBoardLocation(int x, int y);
};

#endif
