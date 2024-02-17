#include "headerFiles/bishop.h"


Bishop::Bishop(int x, int y, int side): Piece(x, y, side), basePath("spritePNGs/bishop")
{basePath += (side==-1) ? "Black.png" : "White.png";}
string Bishop::getBasePath() const {
    return basePath;
}
int Bishop::getPieceType() const {
    return 4;
}

