## chessGame makefile
# David Mamujee and Jonathan Smith

CC = g++
CXXFLAGS = -Wall -g -MMD -I/usr/X11/include -L/usr/X11/lib -lX11 -DDEBUG #-DDEBUG1 -DDEBUG2 -DDEBUG3 -DDEBUGMOVES
X11FLAGS = -I/usr/X11R6/include -L/usr/X11R6/lib -lX11

OBJS = view.o textDisplay.o piece.o king.o queen.o bishop.o knight.o rook.o pawn.o game.o controller.o player.o human.o computer.o windowDisplay.o
DEPENDS = $(OBJS:.o=.d)

EXEC = chessGame

# Builds the main.cc file as the program
$(EXEC) : $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) main.cc -o $(EXEC) $(X11FLAGS)

#get all *.d depends files
-include ${DEPENDS}

.PHONY: clean
clean:
	\rm *.o $(EXEC)
