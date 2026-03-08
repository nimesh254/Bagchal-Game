#ifndef AI_H
#define AI_H

#include <vector>
using namespace std;

struct Move{
    int r1,c1,r2,c2;
    bool capture;
};

Move goatAI(vector<vector<char>> board,bool placementPhase);
Move tigerAI(vector<vector<char>> board);

#endif