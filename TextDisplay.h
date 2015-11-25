#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <sstream>
#include "view.h"

class TextDisplay : public View {
  char **theDisplay;          //the n x n display 
  
 public:
  TextDisplay(); //ctor

  ~TextDisplay(); //dtor
  
  //The Controller calls notify to update the (row,column) location to be ch
  virtual void notify(int row, int column, char ch);

  //Prints the Grid
  virtual void print(std::ostream &out) const ;
};

#endif
