#pragma once
#include "std_lib_facilities.h"
#include "pieces.h"


class King : public Piece {
    public:
    King(int x, int y, int side);
    
    int getPieceType() const override;
    vector<TDT4102::Point> getLegalMoves(int (&map)[8][8]) override;
};


