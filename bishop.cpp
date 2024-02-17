#include "headerFiles/bishop.h"


Bishop::Bishop(int x, int y, int side): Piece(x, y, side)
{}
int Bishop::getPieceType() const {
    return 4;
}
vector<TDT4102::Point> Bishop::getLegalMoves(int (&map)[8][8]) {
    vector<TDT4102::Point> moves;
    TDT4102::Point move;
    move.x = coordinate.x;
    move.y = coordinate.y;
    //Opp til venstre
    while(move.y > -1){
        move.x -= padX;
        move.y -= padY;
        if(map[move.x/padX][move.y/padY]*side < 0){    
            moves.push_back(move);
            break;
        }
        else if(map[move.x/padX][move.y/padY]*side == 0){    
            moves.push_back(move);
        }
        else{break;}
    }
    //opp til høyre
    move.x = coordinate.x;
    move.y = coordinate.y;
    while(move.y > -1){
        move.x += padX;
        move.y -= padY;
        if(map[move.x/padX][move.y/padY]*side < 0){    
            moves.push_back(move);
            break;
        }
        else if(map[move.x/padX][move.y/padY]*side == 0){    
            moves.push_back(move);
        }
        else{break;}
    }

    //ned til venstre
    move.x = coordinate.x;
    move.y = coordinate.y;
    while(move.y < 8*padY + 1){
        move.x -= padX;
        move.y += padY;
        if(map[move.x/padX][move.y/padY]*side < 0){    
            moves.push_back(move);
            break;
        }
        else if(map[move.x/padX][move.y/padY]*side == 0){    
            moves.push_back(move);
        }
        else{break;}
    }

    //ned til høyre
    move.x = coordinate.x;
    move.y = coordinate.y;
    while(move.y < 8*padY+1){
        move.x += padX;
        move.y += padY;
        if(map[move.x/padX][move.y/padY]*side < 0){    
            moves.push_back(move);
            break;
        }
        else if(map[move.x/padX][move.y/padY]*side == 0){    
            moves.push_back(move);
        }
        else{break;}
    }


    return moves;
}