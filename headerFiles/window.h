#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "gameLogicSupport.h"

using namespace TDT4102;





class SjakkWindow : public AnimationWindow {
    public:
    //initialisering
    SjakkWindow();

    //Visuelt
    void drawBoard();
    void drawLegalMoves(vector<TDT4102::Point>& legalMoves);
    void drawPieces(int (&map)[8][8]);
    void drawAroundActivePiece(TDT4102::Point cord);
    void drawClock(int timeWhitems, int timeBlackms);
    void drawUndo();
    void drawForward();
    void drawLastMove(TDT4102::Point from, TDT4102::Point to);


    private:
    



};


