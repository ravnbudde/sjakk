#include "headerFiles/rook.h"

Rook::Rook(int x, int y, int side): Piece(x, y, side)
{}
int Rook::getPieceType() const {
    return 5;
}
vector<TDT4102::Point> Rook::getLegalMoves(int (&map)[8][8]) {
    vector<TDT4102::Point> moves;
    TDT4102::Point move;
    move.x = coordinate.x;
    move.y = coordinate.y;
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
    move.y = coordinate.y;
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
    move.y = coordinate.y;
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
    move.x = coordinate.x;
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
