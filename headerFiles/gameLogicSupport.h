#include "std_lib_facilities.h"
#pragma once
#include "pieces.h"
#include "Point.h"

//vanlig startbrett FEN
constexpr string_view newBoardFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0";

//Standard square brett, winH:winW = 8:10
constexpr int winH = 800;
constexpr int winW = 1000;

constexpr int padX = winW/10;
constexpr int padY = winH/8;

const TDT4102::Image whitePawnSprite{"spritePNGs/pawnWhite.png"};
const TDT4102::Image whiteHorseSprite{"spritePNGs/horseWhite.png"};
const TDT4102::Image whiteBishopSprite{"spritePNGs/bishopWhite.png"};
const TDT4102::Image whiteRookSprite{"spritePNGs/rookWhite.png"};
const TDT4102::Image whiteQueenSprite{"spritePNGs/queenWhite.png"};
const TDT4102::Image whiteKingSprite{"spritePNGs/kingWhite.png"};
const TDT4102::Image blackPawnSprite{"spritePNGs/pawnBlack.png"};
const TDT4102::Image blackHorseSprite{"spritePNGs/horseBlack.png"};
const TDT4102::Image blackBishopSprite{"spritePNGs/bishopBlack.png"};
const TDT4102::Image blackRookSprite{"spritePNGs/rookBlack.png"};
const TDT4102::Image blackQueenSprite{"spritePNGs/queenBlack.png"};
const TDT4102::Image blackKingSprite{"spritePNGs/kingBlack.png"};


const map<char, int> PieceTypeToInt{
    {'k', -10},
    {'q', -9},
    {'r', -5},
    {'b', -4},
    {'h', -3},    
    {'p', -1},
    {'P', 1}, 
    {'H', 2}, 
    {'B', 4}, 
    {'R', 5}, 
    {'Q', 9}, 
    {'K', 10}
    
};

const map<int, char> IntToPieceType{
    {1,'P'}, 
    {3,'H'}, 
    {4,'B'}, 
    {5,'R'}, 
    {9,'Q'}, 
    {10,'K'},
    {-1,'p'},
    {-3,'h'},
    {-4,'b'},
    {-5,'r'},
    {-9,'q'},
    {-10,'k'}
};

int pieceTypeToInt(const char charType);
char intToPieceType(const int intType);


enum class MoveType{
    NORMAL = 0,
    PAWNPUSH,
    CAPTURE,
    CASTLE,
    ENPASSANT,
    PROMOTION
};


const map<TDT4102::Point, string> PointToCord{
    {TDT4102::Point(0,0), "a8"}, {TDT4102::Point(1,0), "b8"}, {TDT4102::Point(2,0), "c8"}, {TDT4102::Point(3,0), "d8"}, {TDT4102::Point(4,0), "e8"}, {TDT4102::Point(5,0), "f8"}, {TDT4102::Point(6,0), "g8"}, {TDT4102::Point(7,0), "h8"},
    {TDT4102::Point(0,1), "a7"}, {TDT4102::Point(1,1), "b7"}, {TDT4102::Point(2,1), "c7"}, {TDT4102::Point(3,1), "d7"}, {TDT4102::Point(4,1), "e7"}, {TDT4102::Point(5,1), "f7"}, {TDT4102::Point(6,1), "g7"}, {TDT4102::Point(7,1), "h7"},
    {TDT4102::Point(0,2), "a6"}, {TDT4102::Point(1,2), "b6"}, {TDT4102::Point(2,2), "c6"}, {TDT4102::Point(3,2), "d6"}, {TDT4102::Point(4,2), "e6"}, {TDT4102::Point(5,2), "f6"}, {TDT4102::Point(6,2), "g6"}, {TDT4102::Point(7,2), "h6"},
    {TDT4102::Point(0,3), "a5"}, {TDT4102::Point(1,3), "b5"}, {TDT4102::Point(2,3), "c5"}, {TDT4102::Point(3,3), "d5"}, {TDT4102::Point(4,3), "e5"}, {TDT4102::Point(5,3), "f5"}, {TDT4102::Point(6,3), "g5"}, {TDT4102::Point(7,3), "h5"},
    {TDT4102::Point(0,4), "a4"}, {TDT4102::Point(1,4), "b4"}, {TDT4102::Point(2,4), "c4"}, {TDT4102::Point(3,4), "d4"}, {TDT4102::Point(4,4), "e4"}, {TDT4102::Point(5,4), "f4"}, {TDT4102::Point(6,4), "g4"}, {TDT4102::Point(7,4), "h4"},
    {TDT4102::Point(0,5), "a3"}, {TDT4102::Point(1,5), "b3"}, {TDT4102::Point(2,5), "c3"}, {TDT4102::Point(3,5), "d3"}, {TDT4102::Point(4,5), "e3"}, {TDT4102::Point(5,5), "f3"}, {TDT4102::Point(6,5), "g3"}, {TDT4102::Point(7,5), "h3"},
    {TDT4102::Point(0,6), "a2"}, {TDT4102::Point(1,6), "b2"}, {TDT4102::Point(2,6), "c2"}, {TDT4102::Point(3,6), "d2"}, {TDT4102::Point(4,6), "e2"}, {TDT4102::Point(5,6), "f2"}, {TDT4102::Point(6,6), "g2"}, {TDT4102::Point(7,6), "h2"},
    {TDT4102::Point(0,7), "a1"}, {TDT4102::Point(1,7), "b1"}, {TDT4102::Point(2,7), "c1"}, {TDT4102::Point(3,7), "d1"}, {TDT4102::Point(4,7), "e1"}, {TDT4102::Point(5,7), "f1"}, {TDT4102::Point(6,7), "g1"}, {TDT4102::Point(7,7), "h1"}
};



const map<string, TDT4102::Point> CordToPoint{
    {"a8", TDT4102::Point(0,0)}, {"b8", TDT4102::Point(1,0)}, {"c8", TDT4102::Point(2,0)}, {"d8", TDT4102::Point(3,0)}, {"e8", TDT4102::Point(4,0)}, {"f8", TDT4102::Point(5,0)}, {"g8", TDT4102::Point(6,0)}, {"h8", TDT4102::Point(7,0)},
    {"a7", TDT4102::Point(0,1)}, {"b7", TDT4102::Point(1,1)}, {"c7", TDT4102::Point(2,1)}, {"d7", TDT4102::Point(3,1)}, {"e7", TDT4102::Point(4,1)}, {"f7", TDT4102::Point(5,1)}, {"g7", TDT4102::Point(6,1)}, {"h7", TDT4102::Point(7,1)},
    {"a6", TDT4102::Point(0,2)}, {"b6", TDT4102::Point(1,2)}, {"c6", TDT4102::Point(2,2)}, {"d6", TDT4102::Point(3,2)}, {"e6", TDT4102::Point(4,2)}, {"f6", TDT4102::Point(5,2)}, {"g6", TDT4102::Point(6,2)}, {"h6", TDT4102::Point(7,2)},
    {"a5", TDT4102::Point(0,3)}, {"b5", TDT4102::Point(1,3)}, {"c5", TDT4102::Point(2,3)}, {"d5", TDT4102::Point(3,3)}, {"e5", TDT4102::Point(4,3)}, {"f5", TDT4102::Point(5,3)}, {"g5", TDT4102::Point(6,3)}, {"h5", TDT4102::Point(7,3)},
    {"a4", TDT4102::Point(0,4)}, {"b4", TDT4102::Point(1,4)}, {"c4", TDT4102::Point(2,4)}, {"d4", TDT4102::Point(3,4)}, {"e4", TDT4102::Point(4,4)}, {"f4", TDT4102::Point(5,4)}, {"g4", TDT4102::Point(6,4)}, {"h4", TDT4102::Point(7,4)},
    {"a3", TDT4102::Point(0,5)}, {"b3", TDT4102::Point(1,5)}, {"c3", TDT4102::Point(2,5)}, {"d3", TDT4102::Point(3,5)}, {"e3", TDT4102::Point(4,5)}, {"f3", TDT4102::Point(5,5)}, {"g3", TDT4102::Point(6,5)}, {"h3", TDT4102::Point(7,5)},
    {"a2", TDT4102::Point(0,6)}, {"b2", TDT4102::Point(1,6)}, {"c2", TDT4102::Point(2,6)}, {"d2", TDT4102::Point(3,6)}, {"e2", TDT4102::Point(4,6)}, {"f2", TDT4102::Point(5,6)}, {"g2", TDT4102::Point(6,6)}, {"h2", TDT4102::Point(7,6)},
    {"a1", TDT4102::Point(0,7)}, {"b1", TDT4102::Point(1,7)}, {"c1", TDT4102::Point(2,7)}, {"d1", TDT4102::Point(3,7)}, {"e1", TDT4102::Point(4,7)}, {"f1", TDT4102::Point(5,7)}, {"g1", TDT4102::Point(6,7)}, {"h1", TDT4102::Point(7,7)}
};

string pointToCord(const TDT4102::Point &point);
TDT4102::Point cordToPoint(const string &cord);


//FEN hjelpefunksjoner
const string getEPfromFEN(const string &FEN);
const string getCastlefromFEN(const string &FEN);
const string getBoardPosfromFEN(const string &FEN);


void print8x8arr(const int (&arr)[8][8]);
