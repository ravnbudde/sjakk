#pragma once
#include "board.h"
#include "window.h"


class Game {
private:
    string gamestate;
    //Tid i ms, 5 min, 5 sek ekstra hvit
    int whiteTime = 305000;
    int blackTime = 300000;

    //ting for undo osv..
    vector<vector<TDT4102::Point>> history;
    vector<Piece*> captureHistory;
    vector<vector<TDT4102::Point>> forwardHistory;
    vector<Piece*> captureForwardHistory;
    void undoMove();
    void forwardMove();
    void clearActiveSquare();
    


public:
    Game();
    Board board;
    SjakkWindow win;
    void playGame();
    void updateTimes();

    TDT4102::Point activeSquare;
    TDT4102::Point moveTo;
    vector<TDT4102::Point> legalMoves;
    

};


void print8x8arr(const int (&arr)[8][8]);