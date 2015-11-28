//#include "game.h"
#include "controller.h"
#include "textDisplay.h"
#include <iostream>

using namespace std;

Controller::Controller() {
	game = 0;//new Game();
	td = new TextDisplay(8);
	whitePlayer = 0;
	blackPlayer = 0;

	// White always goes first
	currentPlayer = WHITE;
	// TODO: Add code for Graphics Window
}

bool Controller::printWinStatus(int currentPlayer) {
	if ( currentPlayer == 1 ) {
		cout << "Congratulations to the White Player for winning!" << endl;
	} else if ( currentPlayer == -1 ) {
		cout << "Congratulations to the Black Player for winning!" << endl;
	} else {
		cout << "Congratulations to " << currentPlayer << " for winning!" << endl;
	}
}

// Start collecting user input for the Game with specified player moving first
void Controller::play(int givenFirstMove = WHITE) {
  srand(time(NULL));
  currentPlayer = givenFirstMove;

  string cmd;
  string whitePlayerInput;
  string blackPlayerInput;
  bool gameOver = false;

  while ( !gameOver && (cin >> cmd) ) {

  	if (cmd == "setup") {
  		// TODO: Check for a different input to give (if loading a game)
  		setup(cin, *game);

  	} else if (cmd == "game") {
  		//
  		// Set player inputs
  		//
  		cin >> whitePlayerInput >> blackPlayerInput;
  		if (whitePlayerInput == "human") {
  			whitePlayer = cin;
  		} else if ( whitePlayerInput == "computer1" ||
  								whitePlayerInput == "computer2" ||
  								whitePlayerInput == "computer3" ||
  								whitePlayerInput == "computer4") {
  			// TODO: Add AI
  			blackPlayer = cin;
  		}
  		if (blackPlayerInput == "human") {
  			blackPlayer = cin;
  		} else if ( blackPlayerInput == "computer1" ||
  								blackPlayerInput == "computer2" ||
  								blackPlayerInput == "computer3" ||
  								blackPlayerInput == "computer4") {
  			// TODO: Add AI
  			blackPlayer = cin;
  		}
  		//
  		// Movement loop
  		//
  		while (cin >> cmd) {
  			if (cmd == "resign") {
  				currentPlayer = currentPlayer * -1;
  				gameOver = true;  				
  				break;
  			} else if (cmd == "move") {
  				string start, end;
  				bool success = false;
  				cin >> start >> end;

  				// Convert start and end to (x,y) locations
  				int startX = getXLocation(start);
  				int startY = getYLocation(start);
  				int endX = getXLocation(end);
  				int endY = getYLocation(end);

  				//
  				// Check for Pawn promotion
  				//
  				// TODO: NOT sure if 'peek()' is the right way to do this?
  				// TODO: Check for wrong pieced
  				if (cin.peek()) {
  					string pawnPromotionPiece;
  					cin >> pawnPromotionPiece;
  					success = game->makeMove(startX, startY, endX, endY, pawnPromotionPiece);
  				} else {
  					success = game->makeMove(startX, startY, endX, endY);
  				}

  				if (!success) {
  					cout << "Couldn't make that move!" << endl;
  				} else {
  					// Check for the big win!
  					// if ( game->hasWon(currentPlayer) ) {
  					// 	gameOver = true;
  					// 	break;
  					// }
  					// or just increment whose turn it is
  					currentPlayer = currentPlayer * -1;
  				}
  			}
  		} // Make another move
  	} // game is over
  }
  printWinStatus(currentPlayer);
}


void Controller::setup(std::istream & input, Game & g) {
	//game.init();
	string cmd;
	while (input >> cmd) {
		if (cmd == "+") {
			string piece, location;
			cin >> piece >> location;
			int x = getXLocation(location);
  		int y = getYLocation(location);
			#ifdef DEBUG
				cout << "'+' " << x << "," << y << " command not recognized" << endl;
			#endif

		} else if (cmd == "-") {
			#ifdef DEBUG
				cout << "'-' " << cmd << " command not recognized" << endl;
			#endif

		} else if (cmd == "=") {
			string colour;
			cin >> colour;
			if (cmd == "white") {
				currentPlayer = WHITE;
			} else if (cmd == "black") {
				currentPlayer = BLACK;
			} else {
				#ifdef DEBUG
				cout << "'=' " << cmd << " command not recognized" << endl;
				#endif
			}

		} else if (cmd == "done") {
			// TODO: Check game for a valid board
			// if (!game.validBoard()) {
			//    continue;
			// } else {
			break;
			// }
		}
	}
}

/*
 * Update the game state in the View
 */
void Controller::notify(int x, int y, char piece) {
	td->notify(x, y, piece);
}

Controller::~Controller() {
	if (game != 0) {
		delete game;
	}
	if (td != 0) {
		delete td;
	}
}

// Returns the x location of a board location
// Requires: location have the format [char][int] such that it would be found
//		on the game board
int getXLocation(string location) {
	char x = location[0];
	int locX = x - 'a';
	return locX;
}

// Returns the y location of a board location
// Requires: location have the format [char][int] such that it would be found
//		on the game board
int getYLocation(string location) {
	char y = location[1];
	int locY = y - '0';
	return locY;
}
