#include "std_lib_facilities.h"
#pragma once
#include "pieces.h"

//Legg til  forskjellig regler osv. i en class?
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





