
#ifndef VIEW_H
#define VIEW_H
#include <iostream>
#include <sstream>

class View {
  protected:
    const int gridSize;
  public:
    View(int n);
    
 /*
  * The Controller calls notify to update the (row,column) location to be ch
  */
 virtual void notify(int x, int y, char ch, bool printOut = true) = 0;
 
 // Modifies two cells in the view
 virtual void notifyTwo(int x, int y, char ch, int x2, int y2, char ch2) = 0;

 virtual void print(std::ostream &out) const = 0;
    
 virtual ~View() = 0;
};

#endif
