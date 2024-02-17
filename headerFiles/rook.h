#pragma once
#include "std_lib_facilities.h"
#include "pieces.h"

class Rook : public Piece {
    public:
    Rook(int x, int y, int side);
    string basePath;

    string getBasePath() const override;
    int getPieceType() const override;
};


