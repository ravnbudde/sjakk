#pragma once
#include "std_lib_facilities.h"
#include "gameLogicSupport.h"


class MoveData{
    public:
    MoveData(string FEN, TDT4102::Point from, TDT4102::Point to, MoveType moveType);//Enten NORMAL eller PAWNPUSH
    MoveData(string FEN, TDT4102::Point from, TDT4102::Point to, const char capturedPiece, MoveType moveType);//Enten CAPTURE eller ENPASSANT
    MoveData(string FEN, TDT4102::Point from, char castleType, MoveType moveType); //castle
    MoveData(string FEN, TDT4102::Point from, TDT4102::Point to, char promotionType, char capturedPiece, MoveType movetype); //promotion med capture


    const string FEN;
    MoveType moveType;
    const string from;
    const string to;

    char capturedPiece = NULL;
    string capturedPawnCord = "";

    char castleType = NULL;
    char promotionType = NULL;

    private:

};

