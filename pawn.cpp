#include "headerFiles/pawn.h"

Pawn::Pawn(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/pawn")
{basePath += (side==-1) ? "Black.png" : "White.png";}
string Pawn::getBasePath() const {
    return basePath;
}
int Pawn::getPieceType() const {
    return 1;
}


