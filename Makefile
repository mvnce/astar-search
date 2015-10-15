CPPFLAGS=-std=c++11 -g -O3

Sort: main.o
	    g++ main.o -o Astar

main.o: main.cpp astar.h
	g++ $(CPPFLAGS) -c main.cpp
