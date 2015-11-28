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

void Controller::printWinStatus(int currentPlayer) {
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
  currentPlayer = givenFirstMove;

  string cmd;
  string whitePlayerInput;
  string blackPlayerInput;
  bool gameOver = false;

  // Welcome message
  cout << "Welcome to Pawn Pusher 9000!" << endl;
  cout << "Commands: 'setup', 'game [white-player] [black-player]'" << endl;

  while ( !gameOver && (cin >> cmd) ) {

  	if (cmd == "setup") {
  		#ifdef DEBUG
				cout << "(Entering setup...)" << endl;
			#endif
  		// TODO: Check for a different input to give (if loading a game)
  		setup(cin, *game);

  	} else if (cmd == "game") {
  		#ifdef DEBUG
				cout << "(Starting game...)" << endl;
			#endif
  		//
  		// Set player inputs
  		//
  		cin >> whitePlayerInput >> blackPlayerInput;
  		if (whitePlayerInput == "human") {
  			whitePlayer = &cin;
  		} else if ( whitePlayerInput == "computer1" ||
  								whitePlayerInput == "computer2" ||
  								whitePlayerInput == "computer3" ||
  								whitePlayerInput == "computer4") {
  			// TODO: Add AI
  			cout << "White: Your computer opponent is getting ready..." << endl;
  			whitePlayer = &cin;
  		} else {
  			cout << "White player is not recognized, try again..." << endl;
				continue;
  		}
  		if (blackPlayerInput == "human") {
  			blackPlayer = &cin;
  		} else if ( blackPlayerInput == "computer1" ||
  								blackPlayerInput == "computer2" ||
  								blackPlayerInput == "computer3" ||
  								blackPlayerInput == "computer4") {
  			// TODO: Add AI
  			cout << "Black: Your computer opponent is getting ready..." << endl;
  			blackPlayer = &cin;
  		} else { 
				cout << "Black player is not recognized, try again..." << endl;
				continue;
			}
  		//
  		// Movement loop
  		//
  		// TODO: switch back and forth between input streams
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

  				// Let the game know who is making the move
  				//game->setCurrentPlayer(currentPlayer);
  				if (cin.peek()) {
  					char pawnPromotionPiece;
  					cin >> pawnPromotionPiece;
  					success = game->makeMove(startX, startY, endX, endY, pawnPromotionPiece);
  				} else {
  					success = game->makeMove(startX, startY, endX, endY);
  				}

  				if (!success) {
  					cout << "Couldn't make that move!" << endl;
  				} else {
  					// Check for the big win!
  					// if ( game->hasWon() ) {
  					// 	gameOver = true;
  					// 	 printWinStatus(currentPlayer);
  					// 	break;
  					// } else if ( game->isStalemate() ) {
  					// gameOver = ture;
  					// cout << "Ended game in stalemate." << endl;
  					//}

  					// or just increment whose turn it is
  					currentPlayer = currentPlayer * -1;
  				}
  			}
  		} // Make another move
  	} // game is over
  }
}

bool Controller::validLocation(char chX, char chY) const {
	if (chX > 'h' || chX < 'a' || 
				chY < '1' || chY > '8') {
		return false;
	}
	return true;
}


void Controller::setup(std::istream & input, Game & g) {
	//game.init();
	string cmd, location;
	char piece;
	while (input >> cmd) {
		if (cmd == "+") {
			cin >> piece >> location;

			// Location validation
			if ( !validLocation(location[0], location[1]) ) {
				cout << "Invalid board location, try again..." << endl;
				continue;
			}

			int x = getXLocation(location);
  		int y = getYLocation(location);
  		// game.addPiece(x,y,piece);
  		notify(x, y, piece);
			#ifdef DEBUG
				cout << "'+' " << x << "," << y << " command not recognized" << endl;
			#endif

		} else if (cmd == "-") {
			cin >> location;

			// Location validation
			if (!validLocation(location[0], location[1]) ) {
				cout << "Invalid board location, try again..." << endl;
				continue;
			}

			int x = getXLocation(location);
  		int y = getYLocation(location);
  		// game.removePiece(x, y);
  		notify(x, y, '\0');

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
// Requires: valid location string of format [a <= letter <= h][1 <= number <= 8]
// Translation:
//  8 -> 0, 7 -> 1, 6 -> 2, 5 -> 3, 4 -> 4, 3 -> 5, 2 -> 6, 1 -> 7
int getXLocation(string location) {
	char x = location[0];
	int locX = x - 'a';
	return locX;
}

// Returns the y location of a board location
// Requires: valid location string of format [a <= letter <= h][1 <= number <= 8]
// Translation:
//  a -> 0, b -> 1, c -> 2, d -> 3, e -> 4, f -> 5, g -> 6, h -> 7
int getYLocation(string location) {
	char y = location[1];
	int locY = y - '1';
	locY = 7 - locY;
	return locY;
}
