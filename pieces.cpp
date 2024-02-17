#include "headerFiles/pieces.h"

Piece::Piece(int x, int y, int side): coordinate{x, y}, side(side)
{}

Piece::~Piece() {}
int Piece::getPieceType() const{
    return 0;
}

vector<TDT4102::Point> Piece::getLegalMoves(int (&map)[8][8]){
    vector<TDT4102::Point> moves;
    return moves;
}














