#include "textdisplay.h"

TextDisplay::TextDisplay(int n):View(n){
	// Creates a new nxn textdisplay and sets the default value to '0'
	theDisplay = new char*[n];
	for (int row = 0; row < n; row++){
		theDisplay[i] = new char[n];

		for (int column = 0; column++ < n; column++){
			//A variable that will know if it is initializng the Piece as a capital or not
			int capital = 0;
			if (row > n/2) capital = 'A' - 'a';

			if (row == 0 || row == n-1){
				//Sets Rooks Position
				if (column == 0 || column == 7) theDisplay[row][column] = 'r' + capital;

				//Sets Knights Position
				if (column == 1 || column == 6) theDisplay[row][column] = 'n' + capital;

				//Sets Bishops position
				if (column == 2 || column == 5) theDisplay[row][column] = 'b' + capital;

				if (column == 3) theDisplay[row][column] = 'q' + capital;

				if (column == 4) theDisplay[row][column] = 'k' + capital;

			}
			//Sets the Pawns to default location
			else if (row == 1 || row == n-2){
				theDisplay[row][column] = 'p' + capital;

			//Sets all other squares to blank
			else {
				theDisplay[row][column] = blankSquare(row,column);
			}

			
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
  		out << n-row+1 << " ";
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
