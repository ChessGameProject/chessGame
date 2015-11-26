# pp9k makefile
# David Mamujee and Jonathan Smith

CC = g++
CXXFLAGS = -Wall -g -MMD 

OBJS = view.o textDisplay.o piece.o game.o controller.o
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
