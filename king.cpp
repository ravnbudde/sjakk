#include "headerFiles/king.h"


King::King(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/king")
{basePath += (side==-1) ? "Black.png" : "White.png";}
string King::getBasePath() const {
    return basePath;
}
int King::getPieceType() const {
    return 10;
}

