#pragma once
#include "std_lib_facilities.h"
#include "gameLogicSupport.h"


class MoveData{
    public:
    MoveData(string FEN, TDT4102::Point from, TDT4102::Point to, MoveType moveType = MoveType::NORMAL);
    MoveData(string FEN, TDT4102::Point from, TDT4102::Point to, const char capturedPiece, MoveType moveType = MoveType::CAPTURE);

    const string FEN;
    MoveType moveType;
    const string from;
    const string to;
    const char capturedPiece = NULL;

    private:


};

