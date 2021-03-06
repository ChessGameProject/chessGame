//#include "game.h"
#include "controller.h"
#include "textDisplay.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "windowDisplay.h"
#include <iostream>

using namespace std;

Controller::Controller(bool graphics) {
	game = new Game();
  game->setNotification(this);
  if (graphics) {
    #ifdef DEBUG
      cout << "Creating Graphical Display..." << endl;
    #endif
    td = new WindowDisplay(8);
  } else {
    #ifdef DEBUG
      cout << "Creating Text Display..." << endl;
    #endif
    td = new TextDisplay();
  }

  // players[0] is white
  // players[1] is black
	players = new Player*[2];

  boardNotInitialized = true;

	// White always goes first
	currentPlayer = WHITE;

	// TODO: Add code for Graphics Window
}

Controller::~Controller() {
  // if (players[0] != 0) {
  //   delete players[0];
  // }
  // if (players[1] != 0) {
  //   delete players[1];
  // }
  delete [] players;
  delete game;
  if (td != 0) {
    delete td;
  }
}


//
// Notify Functions
//
void Controller::notify(int x, int y, char piece) {
  if (boardNotInitialized) {
    // Don't print out on first board initialization
    td->notify(x, y, piece, false);
  } else {
    td->notify(x, y, piece);
  }
}

void Controller::notifyTwo(int x, int y, char ch, int x2, int y2, char ch2) {
  td->notifyTwo(x,y,ch,x2,y2,ch2);
}

//
// Play
//
// Start collecting user input for the Game with specified player moving first
void Controller::play() {
  srand(time(NULL));

  string cmd;

  // Welcome message
  cout << "Welcome to Pawn Pusher 9000!" << endl;
  cout << "Commands: 'setup', 'game [white-player] [black-player]'" << endl;
  while (cin >> cmd) {
    //
    // SETUP
    //
  	if (cmd == "setup") {
      //Run game initialization to set up default board, then we can change it
      if (boardNotInitialized) {
        game->init();
        td->print(cout);
        cout << "Standard board initialized" << endl;
        boardNotInitialized = false;
      }

      // Welcome information
      cout << "Welcome to SETUP mode" << endl;
      cout << "Commands: '+ [Piece] [Location]', '- [Location]', '= [Player]', 'done'" << endl;
  		setup(cin);

    //
    // GAME
    //
  	} else if (cmd == "game") {
  		#ifdef DEBUG
				cout << "(Starting game...)" << endl;
			#endif
      if (boardNotInitialized) {
        cout << "Make sure a board is setup first!" << endl;
        continue;
      }

  		//
  		// Set player inputs
  		//
      string playerInput;
      bool goodPlayers = true;
      for (int i = 0; i < 2; i++) {
        // Get rid of any old players...
        if (players[i] != 0) {
          delete players[i];
        }

        cin >> playerInput;
        int playerNumber = WHITE;
        if (i == 1) playerNumber = BLACK;
        
        if (playerInput == "human") {
          players[i] = new Human(this);
        } else if (playerInput == "computer1") {
          players[i] = new Computer(this,game,false,1,playerNumber);
        } else if (playerInput == "computer1auto") {
          players[i] = new Computer(this,game,true,1,playerNumber);
        } else if (playerInput == "computer2") {
          players[i] = new Computer(this,game,false,2,playerNumber);
        } else if (playerInput == "computer2auto") {
          players[i] = new Computer(this,game,true,2,playerNumber);
        } else {
          cout << "Player not recognized, try again..." << endl;
          goodPlayers = false;
          break;
        }
      }

      // If players aren't spelled right, try again...
      if (!goodPlayers) continue;

      move();

  	} // 'game' commands endpoint
    cout << "Commands: 'setup', 'game [white-player] [black-player]'" << endl;
  }

  // Output final score
  cout << "Final Score:" << endl;
  cout << "White: " << game->getWhiteScore() << endl;
  cout << "Black: " << game->getBlackScore() << endl;

  // Clean up view so if it is graphical it will close now
  delete td;
  td = 0;
}

// Returns true if gameOver
void Controller::move() {
  bool gameOver = false;
  string cmd;
  if ( currentPlayer == -1 ) {
    cout << "Black's turn:" << endl;
  } else if ( currentPlayer == 1 ) {
    cout << "White's turn:" << endl;
  }


  Player *player = players[0];
  if (currentPlayer == BLACK) {
    player = players[1];
  }

  while (!gameOver) {
    bool success = false;

    // Move is either 'resign' or 'move start end [promotion]'
    istringstream input(player->getNextMove());
    input >> cmd;
    if (cmd == "quit") {
      break;
    } else if (cmd == "resign") {
      if (currentPlayer == WHITE) {
        game->incrementBlackScore();
      } else if (currentPlayer == BLACK) {
        game->incrementWhiteScore();
      }

      currentPlayer = currentPlayer * -1;
      gameOver = true;          
      break;
    } else if (cmd == "move") {
      string start, end;
      input >> start >> end;

      // Convert start and end to (x,y) locations
      int startX = getXLocation(start);
      int startY = getYLocation(start);
      int endX = getXLocation(end);
      int endY = getYLocation(end);

      //
      // Check for Pawn promotion
      //
      // TODO: NOT sure if 'peek()' is the right way to do this?
      // TODO: Check if you can actually promote the pawn to that piece

      // Let the game know who is making the move
      game->setCurrentPlayer(currentPlayer);
      char next = cin.peek();
      if (next == 'Q' || next == 'K') { // TODO: ...
        #ifdef DEBUG
          cout << "! Expecting Pawn Promotion !" << endl;
        #endif
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
        if ( game->hasWon() ) {
          gameOver = true;
          printWinStatus(currentPlayer);
          break;
        } else if ( game->isStalemate() ) {
          gameOver = true;
          cout << "Ended game in stalemate." << endl;
          break;
        }

        // or just increment whose turn it is
        currentPlayer = currentPlayer * -1;
        if (currentPlayer == WHITE) {
          player = players[0];
        } else {
          player = players[1];
        }
      }
    }
    if ( currentPlayer == -1 ) {
      cout << "Black's turn:" << endl;
    } else if ( currentPlayer == 1 ) {
      cout << "White's turn:" << endl;
    }
  } // Make another move

  // RESET THE BOARD
  game->clearGame(true);
  boardNotInitialized = true;
}

void Controller::setup(std::istream & input) {
	string cmd, location;
	char piece;
	while (input >> cmd) {
    #ifdef DEBUG
      cout << "Received setup command: " << cmd << endl;
    #endif
		if (cmd == "+") {
			input >> piece >> location;

			// Location validation
			if ( !validLocation(location[0], location[1]) ) {
				cout << "Invalid board location, try again..." << endl;
				continue;
			} else if ( !validPiece(piece) ) {
				cout << "Invalid piece, try again" << endl;
			}

			int x = getXLocation(location);
  		int y = getYLocation(location);
      //
      // ADD the piece to the board
      //
  		game->addPiece(x,y,piece);

		} else if (cmd == "-") {
			input >> location;

			// Location validation
			if (!validLocation(location[0], location[1]) ) {
				cout << "Invalid board location, try again..." << endl;
				continue;
			} else if ( !validPiece(piece) ) {
				cout << "Invalid piece, try again" << endl;
        continue;
			}

			int x = getXLocation(location);
  		int y = getYLocation(location);
      //
      // REMOVE the piece to the board
      //
  		game->removePiece(x, y);

		} else if (cmd == "=") {
			string colour;
			input >> colour;
			if (colour == "white") {
				currentPlayer = WHITE;
			} else if (colour == "black") {
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
      // Print out the board one last time
      td->print(cout);
			break;
			// }
		} else {
      cout << cmd << " command not recognized" << endl;

    }
	}
}

// Set the currentPlayer
void Controller::setCurrentPlayer(int player) {
  currentPlayer = player;
}

// Set the boardNotInitialized
void Controller::setBoardNotInitialized(bool b) {
  boardNotInitialized = b;
}
// Get the boardNotInitialized
bool Controller::getBoardNotInitialized() {
  return boardNotInitialized;
}


//
// LOCATION
//

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

// Checks to see if given characters form a valid location
bool Controller::validLocation(char chX, char chY) const {
  if (chX > 'h' || chX < 'a' || 
        chY < '1' || chY > '8') {
    return false;
  }
  return true;
}

// Checks to see if given character p is a valid piece
bool Controller::validPiece(char p) const {
  if (p == 'K' || p == 'k' || p == 'Q' || p == 'q' || p == 'B' || p == 'b' ||
      p == 'N' || p == 'n' || p == 'R' || p == 'r' || p == 'P' || p == 'p') {
    return true;
  }
  return false;
}

// Checks to see if given move is a PawnPromotion
bool Controller::isPawnPromotion(string start, string end) const {
  int startX = getXLocation(start);
  int startY = getYLocation(start);
  int endX = getXLocation(end);
  int endY = getYLocation(end);
  if (game->isPawnPromotion(startX, startY, endX, endY)) return true;
  else return false;
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


