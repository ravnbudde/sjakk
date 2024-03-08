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


void print8x8arr(const int (&arr)[8][8]){
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            cout << arr[x][y] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}


const string getEPfromFEN(const string &FEN){
    int indexCount = 0;
    const char whitespace = ' ';
    string output = "";
    for(int i = 0; i < FEN.length(); i++){
        if(FEN[i] == whitespace){
            indexCount += 1;
            if(indexCount == 4){
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

const string getCaptureEPfromFEN(const string &FEN){
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

const string getCastlefromFEN(const string &FEN){
    int indexCount = 0;
    const char whitespace = ' ';
    string output = "";
    for(int i = 0; i < FEN.length(); i++){
        if(FEN[i] == whitespace){
            indexCount += 1;
            if(indexCount == 3){
                return output;
            }
            output = "";
        }
        else{
            output += FEN[i];
        }
    }
    return "Didnt find castle element in FEN";
}

const string getBoardPosfromFEN(const string &FEN){
    const char whitespace = ' ';
    string output = "";
    for(int i = 0; i < FEN.length(); i++){
        if(FEN[i] == whitespace){
            return output;
        }
        else{
            output += FEN[i];
        }
    }
    return "Didnt find move element in FEN";
}

int getTurnfromFEN(const string &FEN){
    int indexCount = 0;
    const char whitespace = ' ';
    string output = "";
    for(int i = 0; i < FEN.length(); i++){
        if(FEN[i] == whitespace){
            indexCount += 1;
            if(indexCount == 2){
                if(output == "w"){
                    return 1;
                }
                else if(output == "b"){
                    return -1;
                }
            }
            output = "";
        }
        else{
            output += FEN[i];
        }
    }
    return 0;
}

int getHMfromFEN(const string &FEN){
    int indexCount = 0;
    const char whitespace = ' ';
    string output = "";
    for(int i = 0; i < FEN.length(); i++){
        if(FEN[i] == whitespace){
            indexCount += 1;
            if(indexCount == 5){
                int a = stoi(output);
                return a;
            }
            output = "";
        }
        else{
            output += FEN[i];
        }
    }
    return -1;
}

int getTMfromFEN(const string &FEN){
    int indexCount = 0;
    const char whitespace = ' ';
    string output = "";
    for(int i = 0; i < FEN.length(); i++){
        if(FEN[i] == whitespace){
            indexCount += 1;
            output = "";
        }
        else{
            output += FEN[i];
        }
    }
    cout << FEN << endl;
    return stoi(output);
}

TDT4102::Point getCastleDestination(const char castleType){
    switch (castleType)
    {
    case 'K':
        return TDT4102::Point(cordToPoint("g1"));
        break;
    case 'Q':
        return TDT4102::Point(cordToPoint("c1"));
        break;
    case 'k':
        return TDT4102::Point(cordToPoint("g8"));
        break;
    case 'q':
        return TDT4102::Point(cordToPoint("c8"));
        break;
    
    default:
        cout << "Ukjent castletype?   (getCastleDestination)" << endl;
        return TDT4102::Point(NULL, NULL);
        break;
    }
}

char getCastleType(TDT4102::Point to){
    switch (to.y)
    {
    case 0:
        switch (to.x)
        {
        case 2:
            return 'q';
            break;
        case 6:
            return 'k';
            break;
        default:
            cout << "point.x er ikke en castletype    (getcastletype())" << endl;
            break;
        }
        break;
    case 7:
        switch (to.x)
        {
        case 2:
            return 'Q';
            break;
        case 6:
            return 'K';
            break;
        default:
            cout << "point.x er ikke en castletype    (getcastletype())" << endl;
            break;
        }
        break;
    
    default:
        cout << "point.y er ikke en castletype    (getcastletype())" << endl;
        break;
    }
    return NULL;
}

char getCastleCorner(TDT4102::Point from){
    switch (from.y)
    {
    case 0:
        switch (from.x)
        {
        case 0:
            return 'q';
            break;
        case 7:
            return 'k';
            break;
        
        default:
            break;
        }
        break;
    case 7:
        switch (from.x)
        {
        case 0:
            return 'Q';
            break;
        case 7:
            return 'K';
            break;
        
        default:
            break;
        }
        break;
    
    default:
        break;
    }
    return NULL;
}

