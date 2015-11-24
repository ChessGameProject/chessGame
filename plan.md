# Pawn Pusher 9000
#### by David Mamujee and Jonathan Smith


## Project Breakdown

Most Important Pieces:
 - Chess Pieces with proper movement constraints
 - Working Game -> View Communication
 - Setup mode
 - Game mode (winning conditions) (multi-player only)

Secondary:
 - AI/Computer Opponent

## Timeline

Wednesday, November 25:
 - Complete Piece class (Jonathan)
     - And implemented child classes of King (K), Queen (Q), Bishop (B), Knight (N), Rook (R), Pawn (P) (Both)
 - Complete View class to visualize board (David)
     - "load a pre-saved game and display the game."
 - Write Tests for Setup Mode (Both)

Thursday, November 26:
 - Complete Game class 
     - With communication to cells and controller (Jonathan)
     - Moving Pieces (David)
     - Capturing Pieces (David)
     - Checkmate/Stalemate and Game end checking (David)
 - Complete Controller class (Jonathan)
 - Working Multi-player game (Both)

 Saturday, November 28:
 - Start working on AI opponent (Both)
 - Graphical Display

## Questions

1. Chess programs usually come with a book of standard opening move sequences. These
are moves from classical strategies that many chess players have memorized. A standard opening
move sequence is typically a list of accepted opening moves and responses to opponents’ moves, for
the first dozen or so moves of the game. Although you are not required to support this, discuss
how you would implement a book of standard openings if required.

 - To implement this, the standard openings could be stored in text files, and as the User made moves, these moves could be compared with the Text files. If the moves of the User match those of a standard opening, the program could then read the appropriate responses of the opening from the file.


2. How would you implement a feature that would allow a player to undo his/her last
move? What about an unlimited number of undos?

 - Inside a text file, a history of all the moves could be stored, and then if a player wants to undo a move, the program could know what the what the position shoudl be after the move undo. If there are a limted amount of udos, then there could be a method that stores the number of undos made, and each time an undo is made the method could be incremented and checked if it is below the limit.

3. Variations on chess abound. For example, four-handed chess is a variant that is played
by four players (search for it!). Outline the changes that would be necessary to make your program
into a four-handed chess game.

 - The dimension of the board would need to change, and two extra array of pieces would need to be initialized for each new player.
 - The isCheck() function would also need to me modified so that only attacks from the oppositions pieces, and not it's allies pieces would classify as and attack on the King


4. Assuming you have already implemented all the commands specified in the Command
Interpreter, how would you implement loading a pre-saved game with maximal code reuse?
 - I would use the setup command to place each piece from the saved game into a new game in the program.

