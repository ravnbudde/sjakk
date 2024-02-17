#pragma once
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



using namespace TDT4102;





class SjakkWindow : public AnimationWindow {
    public:
    //initialisering
    SjakkWindow();
    void piecesNewSetup();

    //Visuelt
    void drawBoard();
    void drawLegalMoves(vector<TDT4102::Point>& legalMoves);
    void drawPieces();
    void drawAroundActivePiece(int cordX, int cordY );

    //er vel egt mer main loop for nå
    void movepiece();

    //promotion
    void promotion(int pieceNr);

    //variabler, Ting til map, for å beregne lovlige trekk osv...
    vector<Piece*> pieces;
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
    void generateMap(int (&map)[8][8]);//oppdaterer map

    private:
    



};


