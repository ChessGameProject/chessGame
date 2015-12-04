#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"
#include "game.h"

class Computer : public Player {

	int level;
	Game* game;
	int player;
	bool automatic;
// protected:
// 	istream *input;

public:
//	void setInput(istream *i);
	Computer(Controller *c, Game* g, bool automatic, int i, int player);

	std::string getNextMove();

	std::string AILevel1();

	std::string AILevel2();

	std::string outputFormat(int startX, int startY, int endX, int endY);
};

#endif
