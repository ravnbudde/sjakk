#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "pieces.h"
#include "pawn.h"
#include "rook.h"
#include "horse.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "gameLogicSupport.h"
#pragma once


using namespace TDT4102;





class SjakkWindow : public AnimationWindow {
    public:
    SjakkWindow();
    void drawBoard();
    void drawLegalMoves(vector<TDT4102::Point>& legalMoves);
    void drawPieces();
    vector<Piece*> pieces;
    void piecesNewSetup();
    
    void movepiece();


    //Ting til map, for å beregne lovlige trekk osv...
    int map[8][8] = {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
    };

    void generateMap(int (&map)[8][8]);

    private:



};


