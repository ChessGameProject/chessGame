# pp9k makefile
# David Mamujee and Jonathan Smith

CC = g++
CXXFLAGS = -Wall -g -MMD #-DDEBUG -DDEBUG1 -DDEBUG2

OBJS = view.o textDisplay.o piece.o king.o queen.o bishop.o knight.o rook.o pawn.o game.o controller.o player.o human.o computer.o
DEPENDS = $(OBJS:.o=.d)

EXEC = pp9k

# Builds the main.cc file as the program
$(EXEC) : $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) main.cc -o $(EXEC)

#get all *.d depends files
-include ${DEPENDS}

.PHONY: clean
clean:
	\rm *.o $(EXEC)
