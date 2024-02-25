#include "headerFiles/horse.h"



Horse::Horse(int side): Piece(side)
{}
int Horse::getPieceType() const {
    return 3;
}
vector<TDT4102::Point> Horse::getLegalMoves(const int (&map)[8][8], TDT4102::Point from) {
    vector<TDT4102::Point> moves;
    TDT4102::Point move;
    int dy = 2;
    int dx = 2;

    
    //de to ned
    move.y = from.y + dy*1;
    move.x = from.x + 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    move.x = from.x - 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    //de to opp
    move.y = from.y - dy*1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    move.x = from.x + 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    //de to høyre
    move.x = from.x +dx*1;
    move.y = from.y + 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    move.y = from.y - 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    //de to venstre
    move.x = from.x - dx*1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    move.y = from.y + 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }

    return moves;    
}


