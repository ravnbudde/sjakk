#include "headerFiles/moveData.h"


MoveData::MoveData(string FEN, TDT4102::Point from, TDT4102::Point to, MoveType moveType): 
FEN{FEN}, from{pointToCord(from)}, to{pointToCord(to)}, moveType{moveType}
{}

MoveData::MoveData(string FEN, TDT4102::Point from, TDT4102::Point to, const char capturedPiece, MoveType moveType):
FEN{FEN}, from{pointToCord(from)}, to{pointToCord(to)}, capturedPiece{capturedPiece}, moveType{moveType}
{
    // if(moveType == MoveType::ENPASSANT){
    // 
    //     capturedPawnCord = getCaptureEPfromFEN(FEN);
    //     cout << "Ble lagd enpassant movetype med cord "<<capturedPawnCord << endl;
    //     // cout << "Og piecetype: " << capturedPiece << endl;
    // }
    // else{cout << "ble lagd en capture movetype som tar en " << capturedPiece << endl;}
}

MoveData::MoveData(string FEN, TDT4102::Point from, char castleType, MoveType moveType = MoveType::CASTLE):
FEN{FEN}, castleType{castleType}, moveType{moveType}, from{pointToCord(from)}, to{pointToCord(getCastleDestination(castleType))}
{}

MoveData::MoveData(string FEN, TDT4102::Point from, TDT4102::Point to, char promotionType, char capturedPiece, MoveType movetype = MoveType::PROMOTION):
FEN{FEN}, moveType{MoveType::PROMOTION}, from{pointToCord(from)}, to{pointToCord(to)}, capturedPiece{capturedPiece}, promotionType{promotionType}
{}

