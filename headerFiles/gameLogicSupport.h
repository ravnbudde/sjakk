#include "std_lib_facilities.h"
#pragma once
#include "pieces.h"

//Legg til  forskjellig regler osv. i en class?

constexpr int winH = 800;
constexpr int winW = 800;

constexpr int padX = winW/8;
constexpr int padY = winH/8;





vector<TDT4102::Point> getLegalMoves(Piece *piece, int (&map)[8][8]);


