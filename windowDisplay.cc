#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>
#include "windowDisplay.h"

using namespace std;

WindowDisplay::WindowDisplay(int size): View(size), width(400), height(400) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 10; ++i) {
      if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      if (!XAllocColor(d,cmap,&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      colours[i]=xcolour.pixel;
  }

  // Setup background grid
  for ( int r = 0; r < gridSize; r++ ) {
    for ( int c = 0; c < gridSize; c++ ) {
      if ( ( r % 2 == 0 && c % 2 == 0 ) || (!(r % 2 == 0) && !(c % 2 == 0))) {
        // Black tiles
        XSetForeground(d, gc, colours[Black]);
        XFillRectangle(d,w,gc, width/gridSize*c, height/gridSize*r, 50, 50);
      } else {
        // White tiles
        XSetForeground(d, gc, colours[White]);
        XFillRectangle(d,w,gc, width/gridSize*c, height/gridSize*r, 50, 50);
      }
    }
  }

  // Setup pieces
  // Keep track of characters in an array
  string msg = "X";
  theDisplay = new XTextItem*[gridSize];
  for (int x = 0; x < gridSize; x++){
    theDisplay[x] = new XTextItem[gridSize];
    for (int y = 0; y < gridSize; y++){

      XSetForeground(d, gc, colours[Orange]);
      Font f = XLoadFont(d, "6x13");
      XTextItem *ti = new XTextItem;
      ti->chars = const_cast<char*>(msg.c_str());
      ti->nchars = msg.length();
      ti->delta = 0;
      ti->font = f;

       // Set XTextItem in grid!
      //theDisplay[x][y] = ti;

      // Draw it
      XDrawText(d, w, gc, x*50+20, y*50-20, ti, 1);
      XSetForeground(d, gc, colours[Black]);
      XFlush(d);
      delete ti;
    }
  }

  XSetForeground(d, gc, colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);
  usleep(2500);
  XSelectInput(d,w,ExposureMask);
  XFlush(d);
  XEvent event;
  XNextEvent(d,&event); //Hang until the window is ready.
  XSelectInput(d,w,0);
}

WindowDisplay::~WindowDisplay() {
  XFreeGC(d, gc);
  XCloseDisplay(d);

  for (int i = 0; i < gridSize; i++){
    delete [] theDisplay[i];  
  }
  delete [] theDisplay;
}

void WindowDisplay::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void WindowDisplay::drawString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  Font f = XLoadFont(d, "6x13");
  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}


void WindowDisplay::drawBigString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);


  //set default font
  Font f = XLoadFont(d, "6x13");


  // Font f = XLoadFont(d, "-*-helvetica-bold-r-normal--*-240-*-*-*-*-*");
  ostringstream name;
  name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";

  XFontStruct * fStruct = XLoadQueryFont(d, name.str().c_str());

  if (fStruct) { //font was found, replace default
    f = fStruct->fid;
  }


  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
//  ti.font = f->fid;
  ti.font = f;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}

void WindowDisplay::showAvailableFonts() {
  int count;
  char** fnts = XListFonts(d, "*", 10000, &count);

  for (int i = 0; i < count; ++i) cout << fnts[i] << endl;
}

void WindowDisplay::notify(int x, int y, char ch, bool printOut) {
  if (ch == '\0') {
    ch = ' ';
  }
  char msg[2] = {ch, '\0'};

  // Reset tile
  if ( ( y % 2 == 0 && x % 2 == 0 ) || (!(y % 2 == 0) && !(x % 2 == 0))) {
    // Black tiles
    XSetForeground(d, gc, colours[Black]);
    XFillRectangle(d,w,gc, width/gridSize*x, height/gridSize*y, 50, 50);
  } else {
    // White tiles
    XSetForeground(d, gc, colours[White]);
    XFillRectangle(d,w,gc, width/gridSize*x, height/gridSize*y, 50, 50);
  }

  XSetForeground(d, gc, colours[Orange]);
  Font f = XLoadFont(d, "6x13");
  XTextItem ti;
  ti.chars = msg;
  ti.nchars = 1;
  ti.delta = 0;
  ti.font = f;

   // Set XTextItem in grid!
  theDisplay[x][y] = ti;

  // Draw it
  XDrawText(d, w, gc, x*50+20, y*50-20, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}

void WindowDisplay::notifyTwo(int x, int y, char ch, int x2, int y2, char ch2) {
  // help
  notify(x,y,ch,false);
  notify(x2,y2,ch2);

}

void WindowDisplay::print(std::ostream &out) const {
  #ifdef DEBUG
    cout << "Update view" << endl;
  #endif
}

