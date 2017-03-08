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
    /**
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(i == 0 || i == 7 || j == 0 || j == 7){
                weightTable[i][j] = 3;
            }
            else if(i == 1 || i == 6 || j == 1 || j == 6){
                weightTable[i][j] = -3;
            }
            else if(i == 2 || i == 5 || j == 2 || j == 5){
                weightTable[i][j] = 1;
            }
            else{
                weightTable[i][j] = -1;
            }
        }
    }
    **/

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

Move *Player::bestMove(vector <Move*> m, Board * b){ 
    int themove = 0;
    int max = -9999999;
    Board * copy;
    for(int i = 0; i < m.size(); i++){
        copy = b->copy();
        copy->doMove(m[i],mySide);
        vector <Move *> opLegalMoves = legalMoves(copy, opSide);
        int min = 99999; 
        Board * copy2;
        for(int j = 0; j < opLegalMoves.size(); j++){
            copy2 = copy->copy();
            copy2->doMove(opLegalMoves[j],opSide);
            vector <Move *> myLegalMoves2 = legalMoves(copy2,mySide);
            Board * copy3;
            for(int k = 0; k < myLegalMoves2.size(); k++){
                copy3 = copy2->copy();
                copy3->doMove(myLegalMoves2[k],mySide);
                vector <Move *> opLegalMoves2 = legalMoves(copy3, opSide);
                Board * copy4;
                for(int w = 0; w < opLegalMoves2.size(); w++){
                    copy4 = copy3->copy();
                    copy4->doMove(opLegalMoves2[w],opSide);
                    if(getScore(copy4) < min){
                        min = getScore(copy4);
                    }

                }

            }
            // if(getScore(copy2) < min){
            //     min = getScore(copy2);
            // }
            /*
            cerr << "Blacks: " << copy2->countBlack() << endl;
            cerr << "Whites: " << copy2->countWhite() << endl;
            cerr << "This one got" << getScore(copy2) << endl;
            */
            delete copy2;
        }
        //cerr << min << endl;
        if(min > max){
            max = min;
            themove = i; 
        }
        delete copy;
    }
    //cerr << "best: " << max << endl;
    return m[themove];
}

int Player::getScore(Board * b){
    int score = 0;
    vector<tuple<int,int,Side>> occupied = b->getOccupied();
    for(int j = 0; j < occupied.size(); j++){
        if(get<2>(occupied[j]) == opSide){
            score -= weightTable[get<0>(occupied[j])][get<1>(occupied[j])];
        }
        else{
            score += weightTable[get<0>(occupied[j])][get<1>(occupied[j])];            
        }
    }
    return score;
}
