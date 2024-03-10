#pragma once
#include "board.h"
#include "window.h"
#include "moveData.h"
#include "gameLogicSupport.h"


class Game {
private:
    string gamestate;
    bool gameOver = false;
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
    Game(string FEN);
    string FEN  = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
   

    Board board;
    SjakkWindow win;
    void playGame2Player();
    void playGameBotVBot();
    void updateTimes();

    TDT4102::Point activeSquare;
    TDT4102::Point moveTo;
    vector<TDT4102::Point> legalMoves;


    int halfMoves = 0;
    int totMoves = 1;
    void generateFEN();

    bool checkForMate(int turn) const;
    bool checkForStaleMate(int turn) const;
    bool checkForThreeMoveRepitition() const;

};


