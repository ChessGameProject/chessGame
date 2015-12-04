#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>
#include "windowDisplay.h"

using namespace std;

WindowDisplay::WindowDisplay(int size): View(size), width(450), height(450) {

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
        XFillRectangle(d,w,gc, 50 + 50*c, 50*r, 50, 50);
      } else {
        // White tiles
        XSetForeground(d, gc, colours[White]);
        XFillRectangle(d,w,gc, 50 + 50*c, 50*r, 50, 50);
      }
    }
  }

  XSetForeground(d, gc, colours[Black]);
  XFillRectangle(d,w,gc, 0, 0, 50, 450);
  XFillRectangle(d,w,gc, 0, 400, 450, 50);
  for (int i = 0; i < 8; i++) {
    char msg[2] = {'0' + 8-i,'\0'};

    XSetForeground(d, gc, colours[White]);
    Font f = XLoadFont(d, "6x13");
    XTextItem ti;
    ti.chars = msg;
    ti.nchars = 1;
    ti.delta = 0;
    ti.font = f;
    XDrawText(d, w, gc, 20, (i+1)*50-20, &ti, 1);


    char msg2[2] = {'a' + i, '\0'};

    XTextItem ti2;
    ti2.chars = msg2;
    ti2.nchars = 1;
    ti2.delta = 0;
    ti2.font = f;
    XDrawText(d, w, gc, (i+1)*50+20, 430, &ti2, 1);
    XSetForeground(d, gc, colours[Black]);
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
    XFillRectangle(d,w,gc, 50 + 50*x, 50*(y), 50, 50);
  } else {
    // White tiles
    XSetForeground(d, gc, colours[White]);
    XFillRectangle(d,w,gc, 50 + 50*x, 50*(y), 50, 50);
  }

  XSetForeground(d, gc, colours[Orange]);
  Font f = XLoadFont(d, "6x13");
  XTextItem ti;
  ti.chars = msg;
  ti.nchars = 1;
  ti.delta = 0;
  ti.font = f;

  // Draw it
  XDrawText(d, w, gc, 50 + x*50+20, (y+1)*50-20, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  //XFlush(d);
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

