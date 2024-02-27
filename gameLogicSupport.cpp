#include "headerFiles/gameLogicSupport.h"

int pieceTypeToInt(const char charType){
    auto a = PieceTypeToInt.find(charType);
    if(a == PieceTypeToInt.end()){
        cout << "Kunne ikke finne piece" << endl;
        cout << "Lette etter " << charType << endl;
        return 0;
    }
    int piece = PieceTypeToInt.at(charType);
    return piece;
}

char intToPieceType(const int intType){
    auto a = IntToPieceType.find(intType);
    if(a == IntToPieceType.end()){
        cout << "Kunne ikke finne piece" << endl;
        cout << "Lette etter " << intType << endl;
        return 'x';
    }
    char piece = IntToPieceType.at(intType);
    return piece;
}

string pointToCord(const TDT4102::Point &point){
    auto a = PointToCord.find(point);
    if(a == PointToCord.end()){
        cout << "Kunne ikke finne point" << endl;
        cout << "Lette etter (" << point.x << ", " << point.y << ")" << endl;
        return "ERROR";
    } 
    string cord = PointToCord.at(point);
    return cord;
}

TDT4102::Point cordToPoint(const string &cord){
    auto a = CordToPoint.find(cord);
    if(a == CordToPoint.end()){
        cout << "Kunne ikke finne cord" << endl;
        cout << "Lette etter: " << cord << endl;
        return TDT4102::Point(0,0);
    } 
    TDT4102::Point point = CordToPoint.at(cord);
    return point;
}




const string getEPfromFEN(const string &FEN){
    int indexCount = 0;
    const char whitespace = ' ';
    string output = "";
    for(int i = 0; i < FEN.length(); i++){
        if(FEN[i] == whitespace){
            indexCount += 1;
            if(indexCount == 4){
                if(output[1] == '6'){output[1] = '5';}
                else if(output[1] == '3'){output[1] = '4';}
                return output;
            }
            output = "";
        }
        else{
            output += FEN[i];
        }
    }
    return "Didnt find en_passant element in FEN";
}

