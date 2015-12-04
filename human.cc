#include "controller.h"
#include "human.h"

using namespace std;


Human::Human(Controller *c) : Player(c) {}

string Human::getNextMove() {
	string cmd;
	cin >> cmd;

	if (cmd == "resign") {
		return cmd;

	} else if (cmd == "move") {
		string start, end;
		char pawnPromotion;


    cin >> start >> end;

    string final = cmd + " " + start + " " + end;

    // Pawn Promotion!!
    if (c->isPawnPromotion(start, end)) {
	 		cin >> pawnPromotion;
	  	final = final + " " + pawnPromotion;
    }
    return final;

	} else if (cin.eof()) {
		return "quit";
	} else {
		return "ERROR";
	}
}
