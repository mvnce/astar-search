//  astar.h
//  astarsearch
//  author: Siyan Ma

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
using namespace std;

struct combine {
    deque<vector<vector<int>>> list;
    deque<int> direct;
    int cnt_expand;
    int cnt_operator;
};

vector<vector<int>> createPuzzle(string inStr) {
    vector<vector<int>> puzzle = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };
    vector<int> data;
    int cnt = 0;
    for (auto c : inStr) {
        if (isdigit(c)) data.push_back((c - '0'));
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            puzzle[i][j] = data[cnt];
            cnt++;
        }
    }
    return puzzle;
}

void printline(vector<vector<int>> puzzle) {
    cout << "(";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 2 && j == 2) cout << puzzle[i][j];
            else cout << puzzle[i][j] << " ";
        }
    }
    cout << ")" << endl;
}

int misplacedTile(vector<vector<int>> puzzle, vector<vector<int>> puzzle_goal) {
    int cnt = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((puzzle[i][j] != puzzle_goal[i][j]) && puzzle[i][j] != 0) cnt++;
        }
    }
    return cnt;
}

int manhattanDist(vector<vector<int>> puzzle, vector<vector<int>> puzzle_goal) {
    int dist = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((puzzle[i][j] != puzzle_goal[i][j]) && puzzle[i][j] != 0) {
                for (int k = 0; k < 3; k++) {
                    for (int n = 0; n < 3; n++) {
                        if (puzzle_goal[k][n] == puzzle[i][j]) dist += abs(k - i) + abs(n - j);
                    }
                }
            }
        }
    }
    return dist;
}

int incorrectRowAndColumn(vector<vector<int>> puzzle, vector<vector<int>> puzzle_goal) {
    int cnt = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((puzzle[i][j] != puzzle_goal[i][j]) && puzzle[i][j] != 0) {
                for (int k = 0; k < 3; k++) {
                    for (int n = 0; n < 3; n++) {
                        if (puzzle_goal[k][n] == puzzle[i][j]) {
                            if (k != i) cnt++;
                            if (n != j) cnt++;
                        }
                    }
                }
            }
        }
    }
    return cnt;
}

vector<vector<int>> movePos(vector<vector<int>> puzzle, int direct) {
    
    int posX = 0, posY = 0;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[i][j] == 0) {
                posX = i;
                posY = j;
            }
        }
    }
    
    switch (direct) {
        case 0: // move down
            if (posX == 2) {
                return puzzle;
            }
            else {
                puzzle[posX][posY] = puzzle[posX + 1][posY];
                puzzle[posX + 1][posY] = 0;
                return puzzle;
            }
            break;
            
            
        case 1: // move up
            if (posX == 0) {
                return puzzle;
            }
            else {
                puzzle[posX][posY] = puzzle[posX - 1][posY];
                puzzle[posX - 1][posY] = 0;
                return puzzle;
            }
            break;
            
        case 2: // move left
            if (posY == 0) {
                return puzzle;
            }
            else {
                puzzle[posX][posY] = puzzle[posX][posY - 1];
                puzzle[posX][posY - 1] = 0;
                return puzzle;
            }
            break;
            
        case 3: // move right
            if (posY == 2) {
                return puzzle;
            }
            else {
                puzzle[posX][posY] = puzzle[posX][posY + 1];
                puzzle[posX][posY + 1] = 0;
                return puzzle;
            }
            break;
            
        default:
            break;
    }
    return puzzle;
}

int findMinPos(vector<int> values) {
    int min = values[0];
    for (size_t i = 0; i < values.size(); i++) {
        if (min > values[i]) {
            min = values[i];
        }
    }
    int pos = int(find(values.begin(), values.end(), min) - values.begin());
    return pos;
}

bool check(deque<vector<vector<int>>> steps, vector<vector<int>> puzzle) {
    for (size_t i = 0; i < steps.size(); i++) {
        if (steps[i] == puzzle) {
            return true;
        }
    }
    return true;
}

combine aStar(vector<vector<int>> puzzle, vector<vector<int>> puzzle_goal, int h = 1) {
    int remain = misplacedTile(puzzle, puzzle_goal);
    int cnt_expand = 0;
    int cnt_operator = 0;
    combine out;
    deque<vector<vector<int>>> steps;
    deque<int> direct;
    
    while (remain != 0) {
        vector<int> values = { -1,-1,-1,-1 };
        
        switch (h) {
            case 1:
                values[0] = misplacedTile(movePos(puzzle, 0), puzzle_goal);
                values[1] = misplacedTile(movePos(puzzle, 1), puzzle_goal);
                values[2] = misplacedTile(movePos(puzzle, 2), puzzle_goal);
                values[3] = misplacedTile(movePos(puzzle, 3), puzzle_goal);
                break;
                
            case 2:
                values[0] = manhattanDist(movePos(puzzle, 0), puzzle_goal);
                values[1] = manhattanDist(movePos(puzzle, 1), puzzle_goal);
                values[2] = manhattanDist(movePos(puzzle, 2), puzzle_goal);
                values[3] = manhattanDist(movePos(puzzle, 3), puzzle_goal);
                break;
                
            case 3:
                values[0] = incorrectRowAndColumn(movePos(puzzle, 0), puzzle_goal);
                values[1] = incorrectRowAndColumn(movePos(puzzle, 1), puzzle_goal);
                values[2] = incorrectRowAndColumn(movePos(puzzle, 2), puzzle_goal);
                values[3] = incorrectRowAndColumn(movePos(puzzle, 3), puzzle_goal);
                break;
                
            default:
                break;
        }
        cnt_expand++;
        
        int minPos = findMinPos(values);
        
        remain = values[minPos];
        vector<vector<int>> new_puzzle = movePos(puzzle, minPos);
        
        if (new_puzzle == puzzle) {
            values[minPos] = 99;
            minPos = findMinPos(values);
            new_puzzle = movePos(puzzle, minPos);
        }
        
        puzzle = new_puzzle;
        
        cnt_operator++;
        steps.push_back(puzzle);
        direct.push_back(minPos);
    }
    
    out.cnt_expand = cnt_expand;
    out.cnt_operator = cnt_operator;
    out.direct = direct;
    out.list = steps;
    
    return out;
}