#pragma once
#include "std_lib_facilities.h"
#include "pieces.h"


class Horse : public Piece {
    public:
    Horse(int x, int y, int side);
    string basePath;

    string getBasePath() const override;
    int getPieceType() const override;
};


