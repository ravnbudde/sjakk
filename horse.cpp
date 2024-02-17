#include "headerFiles/horse.h"



Horse::Horse(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/horse")
{basePath += (side==-1) ? "Black.png" : "White.png";}
string Horse::getBasePath() const {
    return basePath;
}
int Horse::getPieceType() const {
    return 3;
}



