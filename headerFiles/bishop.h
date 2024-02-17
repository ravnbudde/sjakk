#pragma once
#include "std_lib_facilities.h"
#include "pieces.h"


class Bishop : public Piece {
    public:
    Bishop(int x, int y, int side);
    string basePath;

    string getBasePath() const override;
    int getPieceType() const override;
};



