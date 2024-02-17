#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#pragma once





class Piece {
    public:
    Piece(int x, int y, int side);
    virtual ~Piece();
    virtual string getBasePath() const;
    virtual int getPieceType() const; //1:pawn, 3: horse, 4: bishop, 5: rook, 9: queen, 10: king

    bool isActive = false; //true om brikken er trykket på
    bool virginMove = true; //false etter første trekk for relevante brikker

    TDT4102::Point coordinate; //Lagre koordinatene til hver enkel piece
    int side; //-1 om sort, 1 om hvit
    TDT4102::Image sprite;
    


};






