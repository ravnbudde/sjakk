#pragma once
#include "std_lib_facilities.h"
#include "pieces.h"



class Queen : public Piece {
    public:
    Queen(int x, int y, int side);
    string basePath;

    string getBasePath() const override;
    int getPieceType() const override;
};


