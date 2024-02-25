#include "headerFiles/rook.h"

Rook::Rook(int side): Piece(side)
{}
int Rook::getPieceType() const {
    return 5;
}
vector<TDT4102::Point> Rook::getLegalMoves(int (&map)[8][8], TDT4102::Point from) {
    vector<TDT4102::Point> moves;
    TDT4102::Point move;
    move.x = from.x;
    move.y = from.y;
    //opp
    while(move.y > -1){
        move.y -= 1;
        if(map[move.x/1][move.y/1]*side < 0){    
            moves.push_back(move);
            break;
        }
        else if(map[move.x/1][move.y/1]*side == 0){    
            moves.push_back(move);
        }
        else{break;}
    }
    //ned
    move.y = from.y;
    while(move.y < 8*1+1){
        move.y += 1;
        if(map[move.x/1][move.y/1]*side < 0){    
            moves.push_back(move);
            break;
        }
        else if(map[move.x/1][move.y/1]*side == 0){    
            moves.push_back(move);
        }
        else{break;}
    }

    //venstre
    move.y = from.y;
    while(move.x > -1){
        move.x -= 1;
        if(map[move.x/1][move.y/1]*side < 0){    
            moves.push_back(move);
            break;
        }
        else if(map[move.x/1][move.y/1]*side == 0){    
            moves.push_back(move);
        }
        else{break;}
    }

    //høyre
    move.x = from.x;
    while(move.x < 8*1+1){
        move.x += 1;
        if(map[move.x/1][move.y/1]*side < 0){    
            moves.push_back(move);
            break;
        }
        else if(map[move.x/1][move.y/1]*side == 0){    
            moves.push_back(move);
        }
        else{break;}
    }


    return moves;
}
