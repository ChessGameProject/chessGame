#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "game.h"
#include <iostream>

class Game;
class View;
class GameNotification;

// More documentation in controller.cc file

class Controller : public GameNotification {

    View *td; // The text display.
//    View *gd; // The graphic display.
    
    Game *game;
    void init(std::istream & input, Game & g);


    
	///Helper to check if the game is in a win state
    //if yes, prints Won to stdout and returns true
    //if no, returns false
    bool checkWin() const;

  public:
    Controller();
    ~Controller();
    void play();
    void notify(int row, int column, char piece);   
};

#endif

