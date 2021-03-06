#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <algorithm>
#include <tuple>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Board * board;
    Side mySide;
    Side opSide;
    int weightTable[8][8] = {
        // {  50, -30,  30,  3,  3,  30, -30,  50},
        // { -30,  -50,  1,  1,  1,  1,  -50, -30},
        // {  30,  1,  1,  1,  1,  1,  1,  30},
        // {  3,  1,  1,  2,  2,  1,  1,  3},
        // {  3,  1,  1,  2,  2,  1,  1,  3},
        // {  30,  1,  1,  1,  1,  1,  1,  30},
        // { -30,  -50,  1,  1,  1,  1,  -50, -30},
        // {  50, -30,  30,  3,  3,  30, -30,  50}
        {  300, -50,  30,  3,  3,  30, -50,  300},
        { -50,  -50,  1,  1,  1,  1,  -50, -50},
        {  30,  1,  1,  1,  1,  1,  1,  30},
        {  3,  1,  1,  2,  2,  1,  1,  3},
        {  3,  1,  1,  2,  2,  1,  1,  3},
        {  30,  1,  1,  1,  1,  1,  1,  30},
        { -50,  -50,  1,  1,  1,  1,  -50, -50},
        {  300, -50,  30,  3,  3,  30, -50,  300}

    };

    Move *doMove(Move *opponentsMove, int msLeft);
    vector <Move *> legalMoves(Board * b, Side side);
    int getScore(Board * b);
    Move * bestMove(vector <Move*> m, Board * b);


    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
