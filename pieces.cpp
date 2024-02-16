#include "headerFiles/pieces.h"

Piece::Piece(int x, int y, int side): coordinate{x, y}, side(side)
{}

Piece::~Piece() {}

string Piece::getBasePath() const{
    return "";
}



Pawn::Pawn(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/pawn")
{basePath += (side==0) ? "Black.png" : "White.png";}
string Pawn::getBasePath() const {
    return basePath;
}


Rook::Rook(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/rook")
{basePath += (side==0) ? "Black.png" : "White.png";}
string Rook::getBasePath() const {
    return basePath;
}


Bishop::Bishop(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/bishop")
{basePath += (side==0) ? "Black.png" : "White.png";}
string Bishop::getBasePath() const {
    return basePath;
}


Horse::Horse(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/horse")
{basePath += (side==0) ? "Black.png" : "White.png";}
string Horse::getBasePath() const {
    return basePath;
}


Queen::Queen(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/queen")
{basePath += (side==0) ? "Black.png" : "White.png";}
string Queen::getBasePath() const {
    return basePath;
}


King::King(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/king")
{basePath += (side==0) ? "Black.png" : "White.png";}
string King::getBasePath() const {
    return basePath;
}


