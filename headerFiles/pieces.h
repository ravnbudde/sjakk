#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "gameLogicSupport.h"






class Piece {
    public:
    Piece(int side);
    //destruktør
    virtual ~Piece();
    virtual int getPieceType() const; //1:pawn, 3: horse, 4: bishop, 5: rook, 9: queen, 10: king

    virtual vector<TDT4102::Point> getLegalMoves(const int (&map)[8][8], TDT4102::Point from);



    bool virginMove = true; //false etter første trekk for relevante brikker

    int side; //-1 om sort, 1 om hvit
    
    


};






