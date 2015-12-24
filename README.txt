File list:
main.cpp
astar.h
Makefile
README.txt

To compile code:
>>make

To run the excutable
>>./Astar -h [number]

example:
<139 arctic:~/cse440/project1 >make
g++ -std=c++11 -g -O3 -c main.cpp
g++ main.o -o Astar
<140 arctic:~/cse440/project1 >./Astar -h 1
Please type in the initial state:
(1 2 0 7 8 3 6 5 4)

The total Number of Nodes Expanded: 6
Initial State: (1 2 0 7 8 3 6 5 4)
DOWN: (1 2 3 7 8 0 6 5 4)
DOWN: (1 2 3 7 8 4 6 5 0)
LEFT: (1 2 3 7 8 4 6 0 5)
LEFT: (1 2 3 7 8 4 0 6 5)
UP: (1 2 3 0 8 4 7 6 5)
RIGHT: (1 2 3 8 0 4 7 6 5)
The total Number of Operators Applied: 6