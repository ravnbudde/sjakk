#include "headerFiles/pawn.h"

Pawn::Pawn(int x, int y, int side): Piece(x, y, side)
{}
int Pawn::getPieceType() const {
    return 1;
}
vector<TDT4102::Point> Pawn::getLegalMoves(int (&map)[8][8]) {
    vector<TDT4102::Point> moves;
    TDT4102::Point move;

    int dy;
    //Hvis sort
    if(side == -1){dy = 1;}
    //Hvis hvit
    else{dy = -1;}


    //Sjekker om du ikke kan gå 2 selv om du burde
    if((!virginMove and coordinate.y==1) or (!virginMove and coordinate.y==6*1)){
        virginMove = true;
    }

    //Sjekker om du kan gå rett fram 2 og/eller 1
    if(map[coordinate.x/1][coordinate.y/1 + dy] == 0){
        move.y = coordinate.y + dy*1;
        move.x = coordinate.x;
        moves.push_back(move);
        if(virginMove and (map[coordinate.x/1][coordinate.y/1 + 2*dy] == 0)){
            move.y = coordinate.y +2*dy*1;
            move.x = coordinate.x;
            moves.push_back(move);
            virginMove = false;
        }
    }


    //Sjekker om du kan ta på skrå
    if(map[coordinate.x/1-1][coordinate.y/1 + dy]*side < 0){
        move.y = coordinate.y+dy*1;
        move.x = coordinate.x - 1;
        moves.push_back(move);
    }
    if(map[coordinate.x/1+1][coordinate.y/1 + dy]*side < 0){
        move.y = coordinate.y+dy*1;
        move.x = coordinate.x + 1;
        moves.push_back(move);
    }

    return moves;

}

