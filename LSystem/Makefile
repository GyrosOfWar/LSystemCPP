CC = g++
CPPFLAGS = -Wall -std=c++11 -g

default: all

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

TurtleDrawing.o: TurtleDrawing.cpp TurtleDrawing.h
	$(CC) $(CPPFLAGS) -c TurtleDrawing.cpp

Rule.o: Rule.cpp Rule.h
	$(CC) $(CPPFLAGS) -c Rule.cpp

LSystem.o: LSystem.cpp LSystem.h
	$(CC) $(CPPFLAGS) -c LSystem.cpp

stdafx.o: stdafx.cpp stdafx.h
	$(CC) $(CPPFLAGS) -c stdafx.cpp

all: main.o TurtleDrawing.o Rule.o LSystem.o stdafx.o
	$(CC) main.o TurtleDrawing.o Rule.o stdafx.o LSystem.o -o LSystem.app -lsfml-graphics -lsfml-window -lsfml-system

clean: 
	rm -f *.o LSystem.app