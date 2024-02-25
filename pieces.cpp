#include "headerFiles/pieces.h"

Piece::Piece(int side): side(side)
{}
Piece::~Piece() {}
int Piece::getPieceType() const{
    return 0;
}

vector<TDT4102::Point> Piece::getLegalMoves(int (&map)[8][8], TDT4102::Point from){
    vector<TDT4102::Point> moves;
    return moves;
}














