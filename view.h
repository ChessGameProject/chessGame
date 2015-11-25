
#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <sstream>

class View {

  public:
    View(int);
    
 /*
  * The Controller calls notify to update the (row,column) location to be ch
  */
 virtual void notify(int row, int column, char ch) = 0;

 virtual void print(std::ostream &out) const = 0;
    
 virtual ~View() = 0;
};

#endif
