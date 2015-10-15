//  main.cpp
//  astarsearch
//  author: Siyan Ma

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include "astar.h"
using namespace std;

int main(int argc, const char * argv[]) {
    cout << "Please type in the initial state: " << endl;
    string in_str = "";
    getline(cin, in_str);
    cout << endl;
    vector<string> direct_str = { "DOWN","UP","LEFT","RIGHT" };
    
    vector<vector<int>> puzzle = createPuzzle(in_str);
    vector<vector<int>> puzzle_goal = createPuzzle("(1 2 3 8 0 4 7 6 5)");
    
    combine out = aStar(puzzle, puzzle_goal, atoi(argv[2]));
    cout << "The total Number of Nodes Expanded: " << out.cnt_expand << endl;
    cout << "Initial State: " << in_str << endl;
    for (int i = 0; i < out.list.size(); i++) {
        cout << direct_str[out.direct[i]] << ": ";
        printline(out.list[i]);
    }
    cout << "The total Number of Operators Applied: " << out.cnt_operator << endl;
    return 0;
}
