#pragma once
#include "std_lib_facilities.h"
#include "pieces.h"

class Pawn : public Piece {
    public:
    Pawn(int x, int y, int side);
    string basePath; //path til brikken sin png fil, legger til hvit eller sort basert på int side

    string getBasePath() const override;
    int getPieceType() const override;
};


