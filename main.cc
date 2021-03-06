#include "controller.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>

using namespace std;

int main(int argc, char *argv[]) {
	bool graphics = false;
	bool loading = false;
	string filename;

	if ( argc > 3 ) {
		// Let the user know how to use the arguments
		cout << "Usage: chessGame [--graphics] [filename]" << endl;
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		string g = "--graphics";
		if ( strcmp(argv[i], g.c_str()) == 0 ) {
			#ifdef DEBUG
				cout << "Graphics Flag" << endl;
			#endif
			graphics = true;
		} else {
			#ifdef DEBUG
				cout << "Loading Board Flag..." << endl;
			#endif
			loading = true;
			filename = argv[i];
		}
	}

	// Create a controller with graphical view or not
	Controller c(graphics);

	if (loading) {
		cout << "Loading " << filename << "..." << endl;
		ifstream file(filename.c_str());

		// Use this string stream to send the controller setup instructions
		stringstream fileinput;
		fileinput << file.rdbuf();
		file.close();

		// This is where we'll store the setup instructions
		string setup = "";

		char piece;
		#ifdef DEBUG
		cout << "Loading pieces..." << endl;
		#endif
		// create setup call for all pieces on the gameboard
		for ( int i = 0; ( (fileinput >> piece) && (i < 64) ); i++ ) {

			// Convert input to strings for sending to setup
			ostringstream tmp_piece;
			tmp_piece << piece;
			string piece_str = tmp_piece.str();


			char x = i%8 + 'a';
			ostringstream tmp_x;
			tmp_x << x;
			string x_str = tmp_x.str();
			// stringstream tmp(x[0]);
			// tmp >> x_str;

			int y = 8 - i/8;
			ostringstream tmp_y;
			tmp_y << y;
			string y_str = tmp_y.str();

			if ( piece == '-' || piece == '_') {
				string setup_add = "- " + x_str + y_str + " ";
				setup += setup_add;
			} else {
				string setup_add = "+ " + piece_str + " " + x_str + y_str + " ";
				setup += setup_add;
			}
		}
		
		// Get starting player
		fileinput >> piece;
		if ( piece == 'W' ) {
			setup += "= white ";
		} else if ( piece == 'B' ) {
			setup += "= black ";
		}
		setup += "done ";

		#ifdef DEBUG
			cout << setup << endl;
		#endif

		istringstream issetup(setup);
		// SETUP TIME!!!
		c.setup(issetup);
		c.setBoardNotInitialized(false);		
	}

	
	c.play();	
	return 0;
}
