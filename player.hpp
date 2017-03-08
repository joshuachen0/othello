#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Board * board;
    Side mySide;
    Side opSide;
    int weightTable[8][8]={
        {3,-2,2,2,2,2,-2,3},
        {-2,-3,1,1,1,1,-3,-2},
        {2,1,1,1,1,1,1,2},
        {2,1,1,1,1,1,1,2},
        {2,1,1,1,1,1,1,2},
        {2,1,1,1,1,1,1,2},
        {-2,-3,1,1,1,1,-3,-2},
        {3,-2,2,2,2,2,-2,3}
    };

    Move *doMove(Move *opponentsMove, int msLeft);
    vector <Move *> legalMoves(Board * b, Side side);
    int getScore(Board * b);
    Move * bestMove(vector <Move*> m, Board * b);


    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
