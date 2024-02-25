#include "headerFiles/pawn.h"

Pawn::Pawn(int side): Piece(side)
{}
int Pawn::getPieceType() const {
    return 1;
}
vector<TDT4102::Point> Pawn::getLegalMoves(int (&map)[8][8], TDT4102::Point from) {
    vector<TDT4102::Point> moves;
    TDT4102::Point move;

    int dy;
    //Hvis sort
    if(side == -1){dy = 1;}
    //Hvis hvit
    else{dy = -1;}


    //Sjekker om du ikke kan gå 2 selv om du burde
    if((!virginMove and from.y==1) or (!virginMove and from.y==6*1)){
        virginMove = true;
    }

    //Sjekker om du kan gå rett fram 2 og/eller 1
    if(map[from.x][from.y + dy] == 0){
        move.y = from.y + dy*1;
        move.x = from.x;
        moves.push_back(move);
        if(virginMove and map[from.x][from.y+2*dy]==0){
            move.y = from.y +2*dy*1;
            move.x = from.x;
            moves.push_back(move);
            virginMove = false;
        }
    }


    //Sjekker om du kan ta på skrå
    if(map[from.x/1-1][from.y/1 + dy]*side < 0){
        move.y = from.y+dy*1;
        move.x = from.x - 1;
        moves.push_back(move);
    }
    if(map[from.x/1+1][from.y/1 + dy]*side < 0){
        move.y = from.y+dy*1;
        move.x = from.x + 1;
        moves.push_back(move);
    }

    return moves;

}

