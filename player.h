#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

class Controller;

class Player {
protected:
	Controller *c;

public:
	// Player constructor to set controller
	Player(Controller *c);

	virtual ~Player();

	virtual std::string getNextMove() = 0;
};

#endif
