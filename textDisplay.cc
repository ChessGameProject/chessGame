#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(int n):View(n){
	// Creates a new nxn textdisplay and sets the default value
	theDisplay = new char*[n];
	for (int x = 0; x < n; x++){
		theDisplay[x] = new char[x];
		for (int y = 0; y++ < n; y++){
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

void TextDisplay::notify(int row, int column, char ch){
 	theDisplay[row][column] = ch;
 }

   
<<<<<<< HEAD
void TextDisplay::print(std::ostream &out) const {
  	for (int x = 0; x < gridSize; x++){
  		out << gridSize-x+1 << " ";
  		for (int y = 0; y < gridSize; y++){
  			out << theDisplay[x][y];
=======
void TextDisplay::print(ostream &out) const {
  	for (int row = 0; row < gridSize; row++){
  		out << gridSize-row+1 << " ";
  		for (int column = 0; column < gridSize; column++){
  			out << theDisplay[row][column];
>>>>>>> master
  		}
  		out << endl;
  	}
  	cout << "  ";
  	for (int i = 0; i < gridSize; i++){
  		cout << 'a' + i;
  	}
  	cout << endl;
  }

  View::~View(){}
