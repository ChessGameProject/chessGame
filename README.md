#chessGame
=======
### by David Mamujee and Jonathan Smith
###November 23, 2015

A single or multi-player chess game implementation.

NOTE: X11 library is required for this program to work. If you do not have it installed, run the folowing commmand in the terminal:
sudo apt-get install libx11-dev

Step 1:
- Make executable by running 'make' command in the terminal. Make sure X11 library is install on the system

Step 2:
- Run executable by running './chessGame' in the terminal
Optional: You can have a graphical board if you run the command './chessGame --graphics'

Step 3:
- Before starting a game you must setup the board. To do this, enter the command 'setup'
- To use the default board setup, enter the commnand 'done', then proceed to Step 4

If you would like a custom board setup:
	- Inside of setup mode the following language is used:
		- '+ [piece] [location]' - Adds Piece
			- e.g. '+ K e1', which would place a white king on the e1 square
			- If a piece is already on that square, it is replaced
			- Captial letters represent White and lowercase letter represent Black
		- '- [location]' - Removes Piece
			- e.g. '- a4' woudl remove the piece at the a4 location
			- If there is no piece at that location, no action is taken
		- '= [colour]' - Change turn
			- e.g. '= black'
			- makes it [colour]'s turn, which is either "white" or "black"
		- 'done' - Exit setup mode
			- Leaves setup mode
			- NOTE: In order to leave setup mode the following coditions must be met:
				- There exists at least one white king and one black king
				- There are no pawns in the first or last rows
				- Neither king is in check


Step 4:
- Now it is time to start a game! The command to start a game is 'game [white-player] [black-player]'
- The parameters [white-player] and [black-player] can either be "human" or computer[1-4]
- e.g 'game human computer2'
	- This would be a game where the human is white and black is a Level 2 Computer

Step 5:
- Now we play the game! To make a move, enter the command 'move [old-location] [new-location]'. This will move the piece that was in the [old-location] to the [new-location] if it is a valid move.
- e.g. move e2 e4
- Then for the computer to make a move, just enter the command 'move' and it will automatically make a move

Now you can enjoy! Have fun playing chess! In order to end the game, send and EOF by typing Ctrl-D

