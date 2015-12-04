#ifndef __WINDOW_DISPLAY_H__
#define __WINDOW_DISPLAY_H__
#include "view.h"
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class WindowDisplay : public View {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
  int width, height;

 public:  

  WindowDisplay(int size = 8);  // Constructor; displays the window.
  ~WindowDisplay();             // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown}; // Available colours.

  //The Controller calls notify to update the (row,column) location to be ch
  void notify(int x, int y, char ch, bool printOut = true);

  // Modifies two cells in the view
  void notifyTwo(int x, int y, char ch, int x2, int y2, char ch2);
  // Not sure...
  void print(std::ostream &out) const;

};

#endif
