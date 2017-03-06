#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
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

    Move *doMove(Move *opponentsMove, int msLeft);
    vector <Move *> legalMoves(Board * b);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
