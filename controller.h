#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "game.h"
#include <iostream>

class View;
class Player;

// More documentation in controller.cc file

class Controller : public GameNotification {

    View *td; // The text display.
//    View *gd; // The graphic display.
    
    Game *game;

    bool boardNotInitialized;

    // Storing an array of pointers to players
    Player** players;
    int currentPlayer;
    
	///Helper to check if the game is in a win state
    //if yes, prints Won to stdout and returns true
    //if no, returns false
    bool checkWin() const;

    // Checks to see if given characters form a valid location
    bool validLocation(char chX, char chY) const;
    // Checks to see if given character p is a valid piece
    bool validPiece(char p) const;

    // Prints a success message for the given player
    void printWinStatus(int currentPlayer);

  public:


    // Controller Constructor creates the game
    Controller();
    // Controller Destructor cleans up game and view
    ~Controller();


    // Main entrance point for the chess game
    void play();

    // Collects user moves for the game from both opponents
    // Returns gameOver status
    void move();

    // Game setup to rearrange pieces on the board
    void setup(std::istream & input);


    // Update the game state in the View
    void notify(int x, int y, char piece);   
    // Update two cells in the View
    void notifyTwo(int x, int y, char ch, int x2, int y2, char ch2);


    // Setter for currentPlayer
    void setCurrentPlayer(int currentPlayer);

    // Setter for boardNotInitialized
    void setBoardNotInitialized(bool b);
    // Getter for boardNotInitialized
    bool getBoardNotInitialized();


};

// Converts board location input (eg. f6)
//    into X location number from 0 to board length -1
int getXLocation(std::string location);

// Converts board location input (eg. f6)
//    into Y location number from 0 to board length -1
int getYLocation(std::string location);

#endif

