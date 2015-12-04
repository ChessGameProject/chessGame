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
<<<<<<< HEAD
    cin >> start >> end;zzz

    // TODO: Check for pawn promotion piece

=======
		char *pawnPromotion = new char[1];
    cin >> start >> end;
>>>>>>> 04cf19a993888e94ea2ad8b64d7cfaf5990816cc
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
