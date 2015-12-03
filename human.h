#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human : public Player {
// protected:
// 	istream *input;

public:
//	void setInput(istream *i);
	Human(Controller *c);

	std::string getNextMove();
};

#endif
