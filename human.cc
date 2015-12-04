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
    cin >> start >> end;

    // TODO: Check for pawn promotion piece

    string final = cmd + " " + start + " " + end;
    return final;

	} else {
		return "ERROR";
	}
}
