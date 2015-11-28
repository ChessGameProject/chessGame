#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "game.h"
#include <iostream>

class View;

// More documentation in controller.cc file

class Controller : public GameNotification {

    View *td; // The text display.
//    View *gd; // The graphic display.
    
    Game *game;

    std::istream* whitePlayer;
    std::istream* blackPlayer;
    int currentPlayer;

    // Game setup
    void setup(std::istream & input, Game & g);
    
	///Helper to check if the game is in a win state
    //if yes, prints Won to stdout and returns true
    //if no, returns false
    bool checkWin() const;

    // Checks to see if location is valid on the board
    bool validLocation(char chX, char chY) const;

    // Prints a success message for the given player
    void printWinStatus(int currentPlayer);

  public:
    // Controller Constructor creates the game
    Controller();
    // Controller Destructor cleans up game and view
    ~Controller();

    // Start collecting user input from the Game
    // Args: 
    //    int givenFirstMove determines the player that starts the game
    void play(int givenFirstMove = WHITE);

    // Update the game state in the View
    void notify(int x, int y, char piece);   
};

// Converts board location input (eg. f6)
//    into X location number from 0 to board length -1
int getXLocation(std::string location);

// Converts board location input (eg. f6)
//    into Y location number from 0 to board length -1
int getYLocation(std::string location);

#endif

