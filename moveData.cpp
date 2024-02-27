#include "headerFiles/moveData.h"


MoveData::MoveData(string FEN, TDT4102::Point from, TDT4102::Point to, MoveType moveType): 
FEN{FEN}, from{pointToCord(from)}, to{pointToCord(to)}, moveType{MoveType::NORMAL}
{}

MoveData::MoveData(string FEN, TDT4102::Point from, TDT4102::Point to, const char capturedPiece, MoveType moveType):
FEN{FEN}, from{pointToCord(from)}, to{pointToCord(to)}, capturedPiece{capturedPiece}, moveType{MoveType::CAPTURE}
{}
