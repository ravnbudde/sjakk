#include "headerFiles/horse.h"



Horse::Horse(int x, int y, int side): Piece(x, y, side)
{}
int Horse::getPieceType() const {
    return 3;
}
vector<TDT4102::Point> Horse::getLegalMoves(int (&map)[8][8]) {
    vector<TDT4102::Point> moves;
    TDT4102::Point move;
    int dy = 2;
    int dx = 2;

    
    //de to ned
    move.y = coordinate.y + dy*1;
    move.x = coordinate.x + 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    move.x = coordinate.x - 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    //de to opp
    move.y = coordinate.y - dy*1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    move.x = coordinate.x + 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    //de to høyre
    move.x = coordinate.x +dx*1;
    move.y = coordinate.y + 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    move.y = coordinate.y - 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    //de to venstre
    move.x = coordinate.x - dx*1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }
    move.y = coordinate.y + 1;
    if(0 <= move.y/1 and move.y/1 <= 7 and 0 <= move.x/1 and move.x/1 <= 7){
    if(map[move.x/1][move.y/1]*side < 1){    
        moves.push_back(move);
    }
    }

    return moves;    
}


