#pragma once
#include "board.h"
#include "window.h"
#include "moveData.h"
#include "gameLogicSupport.h"


class Game {
private:
    string gamestate;
    //Tid i ms, 5 min, 5 sek ekstra hvit
    int whiteTime = 305000;
    int blackTime = 300000;

    //ting for undo osv..
    vector<MoveData> history;
    vector<MoveData> forwardHistory;
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


    int halfMoves = 0;
    string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0";
    void generateFEN();

};


void print8x8arr(const int (&arr)[8][8]);