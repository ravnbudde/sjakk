#pragma once
#include "std_lib_facilities.h"
#include "pieces.h"


class King : public Piece {
    public:
    King(int x, int y, int side);
    string basePath;

    string getBasePath() const override;
    int getPieceType() const override;
};


