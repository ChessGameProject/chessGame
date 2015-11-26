#include "textdisplay.h"

TextDisplay::TextDisplay(int n):View(n){
	// Creates a new nxn textdisplay and sets the default value
	theDisplay = new char*[n];
	for (int row = 0; row < n; row++){
		theDisplay[row] = new char[n];
		for (int column = 0; column++ < n; column++){
			theDisplay[row][column] = blankSquare(row,column);
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

void TextDisplay::notify(int row, int column, char ch){
 	theDisplay[row][column] = ch;
 }

   
void TextDisplay::print(std::ostream &out) const {
  	for (int row = 0; row < gridSize; row++){
  		out << gridSize-row+1 << " ";
  		for (int column = 0; column < gridSize; column++){
  			out << theDisplay[row][column];
  		}
  		out << std::endl;
  	}
  	cout << "  ";
  	for (int i = 0; i < gridSize; i++){
  		cout << 'a' + i;
  	}
  	cout << endl;
  }

  View::~View(){}
