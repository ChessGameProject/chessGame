#include "human.h"

using namespace std;

// Set input so we can accept user commands through interface
// Human::setInput(istream *i) {
// 	input = i;
// }

Human::Human(Controller *c) : Player(c) {}

string Human::getNextMove() {
	string cmd;
	cin >> cmd;

	if (cmd == "resign") {
		return cmd;

	} else if (cmd == "move") {
		string start, end;
		char *pawnPromotion = new char[1];
    cin >> start >> end;
    string final = cmd + " " + start + " " + end;

    cin.readsome(pawnPromotion, 1);
    #ifdef DEBUG
    	cout << "PawnPromo: " << pawnPromotion[0] << endl;
    #endif
  	if (pawnPromotion > 0) {
  		final = final + " " + pawnPromotion;
  	}
  	delete pawnPromotion;

    return final;

	} else {
		return "ERROR";
	}
}
