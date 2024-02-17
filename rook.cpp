#include "headerFiles/rook.h"

Rook::Rook(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/rook")
{basePath += (side==-1) ? "Black.png" : "White.png";}
string Rook::getBasePath() const {
    return basePath;
}
int Rook::getPieceType() const {
    return 5;
}

