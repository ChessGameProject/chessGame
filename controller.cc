#include "game.h"
#include "controller.h"
#include <iostream>

using namespace std;

Controller::Controller() {
	game = new Game();
	td = new TextDisplay(8);
	// TODO: Add code for Graphics Window
}

// White starts game by default
void Controller::play() {
	play(WHITE);
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
void Controller::play(int givenFirstMove) {
  srand(time(NULL));
  int currentPlayer = givenFirstMove;

  string cmd;
  string whitePlayerInput;
  string blackPlayerInput;
  bool gameOver = false;

  while ( !gameOver && (cin >> cmd) ) {

  	if (cmd == "setup") {
  		string setup;
  		// Standard Game Initialization

  		// TODO: Setup
  		while (cin >> setup) {
  			if (cmd == "+") {

  			} else if (setup == "-") {

  			} else if (setup == "=") {
  				string colour;
  				cin >> colour;
  				if (setup == "white") {
  					move = WHITE;
  				} else if (setup == "black") {
  					move = BLACK;
  				} else {
  					#ifdef DEBUG
  					cout << "'=' " << setup << " command not recognized" << endl;
  					#endif
  				}

  			} else if (setup == "done") {
  				// TODO: Check game for a valid board
  				// if (notValid) {
  				//    continue;
  				// } else {
  				break;
  				// }
  			}
  		}

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
  				bool success;
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
  				if (cin.peek()) {
  					string pawnPromotionPiece;
  					cin >> pawnPromotionPiece;
  					success = game.makeMove(startX, startY, endX, endY, pawnPromotionPiece);
  				} else {
  					success = game.makeMove(startX, startY, endX, endY);
  				}

  				if (!success) {
  					cout << "Couldn't make that move!" << endl;
  				} else {
  					// Check for the big win!
  					if ( game.hasWon(currentPlayer) ) {
  						gameOver = true;
  						break;
  					}
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
	//

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

// Keep track of whose play it is
