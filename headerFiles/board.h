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


class Board {
private:
    TDT4102::Point en_passant;
    void BoardNewSetup();


public:
    Board();
    ~Board();
    Piece* the_board[8][8];
    Piece* pieceAt(TDT4102::Point point);
    void PlacePieceAt(Piece* piece, TDT4102::Point point);
    void Move(TDT4102::Point from, TDT4102::Point to); 
    bool TryToMove(TDT4102::Point from, TDT4102::Point to) const;
    bool TryToMoveFiltered(TDT4102::Point from, TDT4102::Point to) const;
    TDT4102::Point GetEnPassant() const;
    int turn;
    bool isInCheck(int side) const;
    vector<TDT4102::Point> filterLegalMoves(TDT4102::Point activeSquare) const;
    bool checkEnPassant(TDT4102::Point activeSquare) const;


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
    void generateMap();//oppdaterer map


    
};
