#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>

class Game;
class View;
class GameNotification;

const int WHITE = 1;
const int BLACK = -1;

// More documentation in controller.cc file

class Controller : public GameNotification {

    View *td; // The text display.
//    View *gd; // The graphic display.
    
    Game *game;

    std::istream & whitePlayer;
    std::istream & blackPlayer;

    // Game setup
    void setup(std::istream & input, Game & g);
    
	///Helper to check if the game is in a win state
    //if yes, prints Won to stdout and returns true
    //if no, returns false
    bool checkWin() const;

  public:
    // Controller Constructor creates the game
    Controller();
    // Controller Destructor cleans up game and view
    ~Controller();

    // Start collecting user input from the Game
    // Args: 
    //    int givenFirstMove determines the player that starts the game
    void play(int);

    // Update the game state in the View
    void notify(int x, int y, char piece);   
};

// Converts board location input (eg. f6)
//    into X location number from 0 to board length -1
int getXLocation(string location);

// Converts board location input (eg. f6)
//    into Y location number from 0 to board length -1
int getYLocation(string location);

#endif

