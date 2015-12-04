#include "textDisplay.h"
using namespace std;

TextDisplay::TextDisplay():View(8){
	// Creates a new nxn textdisplay and sets the default value
	theDisplay = new char*[gridSize];
	for (int x = 0; x < gridSize; x++){
		theDisplay[x] = new char[gridSize];
		for (int y = 0; y < gridSize; y++){
			theDisplay[x][y] = blankSquare(x,y);
		}
	}
}


TextDisplay::~TextDisplay(){
	for (int i = 0; i < gridSize; i++){
		delete [] theDisplay[i];	
	}
	delete [] theDisplay;
}


char TextDisplay::blankSquare(int x, int y){
	if (x%2 == 0){
		if (y%2 == 0) return '_';
		else return ' ';
	}
	else {
		if (y%2 == 0) return ' ';
		else return '_';
	}
}

void TextDisplay::notify(int x, int y, char ch, bool printOut){
	if (ch == '\0') {
		ch = blankSquare(x, y);
	}
	theDisplay[y][x] = ch;
	// Show updated display
	if (printOut) print(cout);
 }

 void TextDisplay::notifyTwo(int x, int y, char ch, int x2, int y2, char ch2){
	notify(x,y,ch,false);
	notify(x2,y2,ch2);
 }


   
void TextDisplay::print(std::ostream &out) const {
	for (int y = 0; y < gridSize; y++){
		out << gridSize-y << " ";
		for (int x = 0; x < gridSize; x++){
			out << theDisplay[y][x];
		}
		out << endl;
	}
	out << "  ";
	for (int i = 0; i < gridSize; i++){
		char x = 'a' + i;
		out << x;
	}
	out << endl;
 }
