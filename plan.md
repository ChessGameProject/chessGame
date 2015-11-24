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

1. Discuss how you would implement a book of standard openings if required.

2. How would you implement a feature that would allow a player to undo his/her last move? What about an unlimited number of undos?

3. Outline the changes that would be necessary to make your program into a four-handed chess game.

4. Assuming you have already implemented all the commands specified in the Command Interpreter, how would you implement loading a pre-saved game with maximal code reuse?
