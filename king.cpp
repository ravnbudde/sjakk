#include "headerFiles/king.h"


King::King(int x, int y, int side): Piece(x, y, side)
{}
int King::getPieceType() const {
    return 10;
}
vector<TDT4102::Point> King::getLegalMoves(int (&map)[8][8]) {
    vector<TDT4102::Point> moves;
    TDT4102::Point move;

    move.x = coordinate.x;
    move.y = coordinate.y;

    for(int i = -1; i < 2; i++){
        move.x = coordinate.x + i*1;
        move.y = coordinate.y - 1;
        if(map[move.x/1][move.y/1]*side < 1){    
            moves.push_back(move);
        }
        if(i!=0){
            move.y = coordinate.y;
            if(map[move.x/1][move.y/1]*side < 1){    
                moves.push_back(move);
            }
        }
        move.y = coordinate.y + 1;
        if(map[move.x/1][move.y/1]*side < 1){    
            moves.push_back(move);
        }
    }

    
    //Castle
    if(virginMove){
        
    }


    return moves;
}
