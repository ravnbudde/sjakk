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


class Board {
private:
    void BoardNewSetup();


public:
    Board(string FEN);
    ~Board();
    Piece* the_board[8][8];
    Piece* pieceAt(TDT4102::Point point);
    void createBoardFromFEN(const string& FEN);
    void deleteAllPieces();
    void PlacePieceAt(const char piece, TDT4102::Point point);
    void Move(TDT4102::Point from, TDT4102::Point to); 
    bool TryToMove(TDT4102::Point from, TDT4102::Point to) const;
    bool TryToMoveFiltered(TDT4102::Point from, TDT4102::Point to) const;
    TDT4102::Point en_passant;
    TDT4102::Point GetEnPassant() const;
    int turn;
    TDT4102::Point getKingCord(int side) const;
    bool isInCheck(int side, TDT4102::Point kingCord) const;
    vector<TDT4102::Point> filterLegalMoves(TDT4102::Point activeSquare) const;
    bool checkEnPassant(TDT4102::Point activeSquare) const;

    string FEN = "";
    bool checkCastleSquares(const char castleType) const;
    TDT4102::Point getCastleDestination(const char castleType) const;
    void moveCastle(char type);


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
