#include "player.hpp"
/* Modification by Josh */
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    board = new Board();
    mySide = side;
    if(mySide == BLACK){opSide = WHITE;}
    else{opSide = BLACK;}
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    board->doMove(opponentsMove,opSide);
    vector <Move *> possiblemoves = legalMoves(board);
    if(possiblemoves.size() == 0){
        return nullptr;
    }
    else{
        board->doMove(possiblemoves[0],mySide);
    }
    return possiblemoves[0];
}

vector <Move *> Player::legalMoves(Board * b){
    vector <Move *> moves;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Move * move = new Move(i,j);
            if(b->checkMove(move,mySide)){
                moves.push_back(move);
            }
            else{
                delete move;
            }
        }
    }
    return moves;
}
