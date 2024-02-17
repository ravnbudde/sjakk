#include "headerFiles/queen.h"


Queen::Queen(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/queen")
{basePath += (side==-1) ? "Black.png" : "White.png";}
string Queen::getBasePath() const {
    return basePath;
}
int Queen::getPieceType() const {
    return 9;
}
