#include "headerFiles/bishop.h"


Bishop::Bishop(int side): Piece(side)
{}
int Bishop::getPieceType() const {
    return 4;
}
vector<TDT4102::Point> Bishop::getLegalMoves(int (&map)[8][8], TDT4102::Point from) {
    vector<TDT4102::Point> moves;
    TDT4102::Point move;
    move.x = from.x;
    move.y = from.y;
    //Opp til venstre
    while(move.y > -1){
        move.x -= 1;
        move.y -= 1;
        if(map[move.x/1][move.y/1]*side < 0){    
            moves.push_back(move);
            break;
        }
        else if(map[move.x][move.y/1]*side == 0){    
            moves.push_back(move);
        }
        else{break;}
    }
    //opp til høyre
    move.x = from.x;
    move.y = from.y;
    while(move.y > -1){
        move.x += 1;
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

    //ned til venstre
    move.x = from.x;
    move.y = from.y;
    while(move.y < 8*1 + 1){
        move.x -= 1;
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

    //ned til høyre
    move.x = from.x;
    move.y = from.y;
    while(move.y < 8*1+1){
        move.x += 1;
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


    return moves;
}