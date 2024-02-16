#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "pieces.h"
#pragma once


using namespace TDT4102;

constexpr int winH = 800;
constexpr int winW = 800;

constexpr int padX = winH/8;
constexpr int padY = winW/8;

constexpr int map[8][8] = {
    {1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1}
};


class SjakkWindow : public AnimationWindow {
    public:
    SjakkWindow();
    void drawBoard();
    void drawPieces();
    vector<Piece*> pieces;
    void piecesNewSetup();
    
    void movepiece();


    private:



};


