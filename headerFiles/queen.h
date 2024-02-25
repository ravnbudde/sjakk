#pragma once
#include "std_lib_facilities.h"
#include "pieces.h"



class Queen : public Piece {
    public:
    Queen(int side);
    
    int getPieceType() const override;
    vector<TDT4102::Point> getLegalMoves(const int (&map)[8][8], TDT4102::Point from) override;
};


