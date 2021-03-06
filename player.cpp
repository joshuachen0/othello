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

    board = new Board();

    mySide = side;
    if (mySide == BLACK) {
        opSide = WHITE;
    }
    else {
        opSide = BLACK;
    }
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
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
    vector <Move *> possiblemoves = legalMoves(board,mySide);
    Move * m;
    if(possiblemoves.size() == 0){
        return nullptr;
    }
    else{
        m = bestMove(legalMoves(board, mySide),board);
        board->doMove(m,mySide);
    }
    return m;
}

vector <Move *> Player::legalMoves(Board * b, Side side){
    vector <Move *> moves;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Move * move = new Move(i,j);
            if(b->checkMove(move,side)){
                moves.push_back(move);
            }
            else{
                delete move;
            }
        }
    }
    return moves;
}

Move *Player::bestMove(vector <Move*> m, Board * b) { 
    int themove = 0;
    int max = -99999;
    Board * copy;

    for (int i = 0; i < m.size(); i++) {
        copy = b->copy();
        copy->doMove(m[i],mySide);
        vector <Move *> opLegalMoves = legalMoves(copy, opSide);
        int min = 99999;

        Board * copy2;
        for (int j = 0; j < opLegalMoves.size(); j++) {
            copy2 = copy->copy();
            copy2->doMove(opLegalMoves[j],opSide);
            vector <Move *> myLegalMoves2 = legalMoves(copy2,mySide);

            Board * copy3;
            for (int k = 0; k < myLegalMoves2.size(); k++) {
                copy3 = copy2->copy();
                copy3->doMove(myLegalMoves2[k],mySide);
                vector <Move *> opLegalMoves2 = legalMoves(copy3, opSide);

                Board * copy4;
                for (int w = 0; w < opLegalMoves2.size(); w++) {
                    copy4 = copy3->copy();
                    copy4->doMove(opLegalMoves2[w],opSide);

                    int score = getScore(copy4);
                    //score += 8 * m.size();
                    score += 8 * myLegalMoves2.size();
                    //score -= 8 * opLegalMoves.size();
                    score -= 8 * opLegalMoves2.size();

                    if (score < min) {
                        min = score;
                    }

                    delete copy4;
                }

                delete copy3;
            }
            
            delete copy2;
        }

        if (min > max) {
            max = min;
            themove = i; 
        }

        delete copy;
    }

    return m[themove];
}

int Player::getScore(Board * b){
    // int score = 0;
    // vector<tuple<int,int,Side>> occupied = b->getOccupied();
    // for(int j = 0; j < occupied.size(); j++){
    //     if(get<2>(occupied[j]) == opSide){
    //         score -= weightTable[get<0>(occupied[j])][get<1>(occupied[j])];
    //     }
    //     else{
    //         score += weightTable[get<0>(occupied[j])][get<1>(occupied[j])];            
    //     }
    // }
    // return score;
    int score = 0;

    bitset<64> taken = b->getTaken();
    bitset<64> black = b->getBlack();
    bitset<64> white = taken & ~ black;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            score += black.test(i*8+j) * weightTable[i][j];
            score -= white.test(i*8+j) * weightTable[i][j];
        }
    }

    return score;    
}
