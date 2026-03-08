#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "ai.h"
using namespace std;

// Player input functions
Move playerMoveGoat(vector<vector<char>> &board, bool placementPhase);
Move playerMoveTiger(vector<vector<char>> &board);

#endif