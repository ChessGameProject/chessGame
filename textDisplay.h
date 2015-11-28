#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <sstream>
#include "view.h"

class TextDisplay : public View {
  char **theDisplay;          //the n x n display 
  
 public:
  TextDisplay(int n); //ctor

  ~TextDisplay(); //dtor
  
  // Function that will return the appropriate representation for a blank square
  // Note: This functions counts the bottom left square as (0,0)
 char blankSquare(int x, int y);
  
  
  //The Controller calls notify to update the (row,column) location to be ch
  virtual void notify(int x, int y, char ch);

  //Prints the Grid
  virtual void print(std::ostream &out) const ;
};

#endif
