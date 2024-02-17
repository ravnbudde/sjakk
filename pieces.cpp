#include "headerFiles/pieces.h"

Piece::Piece(int x, int y, int side): coordinate{x, y}, side(side)
{}

Piece::~Piece() {}

string Piece::getBasePath() const{
    return "";
}

int Piece::getPieceType() const{
    return 0;
}














