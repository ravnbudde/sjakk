#include "headerFiles/king.h"


King::King(int side): Piece(side)
{}
int King::getPieceType() const {
    return 10;
}
vector<TDT4102::Point> King::getLegalMoves(const int (&map)[8][8], TDT4102::Point from) {
    vector<TDT4102::Point> moves;
    TDT4102::Point move;

    move.x = from.x;
    move.y = from.y;

    for(int i = -1; i < 2; i++){
        move.x = from.x + i*1;
        move.y = from.y - 1;
        if(map[move.x/1][move.y/1]*side < 1){    
            moves.push_back(move);
        }
        if(i!=0){
            move.y = from.y;
            if(map[move.x/1][move.y/1]*side < 1){    
                moves.push_back(move);
            }
        }
        move.y = from.y + 1;
        if(map[move.x/1][move.y/1]*side < 1){    
            moves.push_back(move);
        }
    }

    return moves;
}
