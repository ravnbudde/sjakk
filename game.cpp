#include "headerFiles/game.h"

Game::Game(): gamestate{"active"}, board{Board{FEN}}, win{SjakkWindow{}}
{
    board.FEN = FEN;
}
Game::Game(string FEN): FEN{FEN}, gamestate{"active"}, board{Board{FEN}}, win{SjakkWindow{}}
{
    halfMoves = getHMfromFEN(FEN);
    totMoves = getTMfromFEN(FEN);
    board.FEN = FEN;
}



void Game::updateTimes(){
    if(board.turn==1){
        whiteTime -= 17;
    }
    else{
        blackTime -= 17;
    }
}

void Game::clearActiveSquare(){
    activeSquare = TDT4102::Point(8,8);
    legalMoves.clear();
}

void Game::generateFEN(){
    const auto& mt = history.back().moveType;
    FEN = "";
    int noPieceCount = 0;
    //Går over alle brikkene
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            if(board.the_board[x][y] == nullptr){
                noPieceCount += 1;
            }
            else{
                switch (board.the_board[x][y]->getPieceType()*board.the_board[x][y]->side)
                {
                case 1:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(1);
                    break;
                case 3:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(3);
                    break;
                case 4:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(4);
                    break;
                case 5:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(5);
                    break;
                case 9:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(9);
                    break;
                case 10:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(10);
                    break;
                case -1:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(-1);
                    break;
                case -3:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(-3);
                    break;
                case -4:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(-4);
                    break;
                case -5:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(-5);
                    break;
                case -9:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(-9);
                    break;
                case -10:
                    if(noPieceCount != 0){
                        FEN += to_string(noPieceCount);
                        noPieceCount = 0;
                    }
                    FEN += intToPieceType(-10);
                    break;

                default:
                    break;
                }
            }
        }
        if(noPieceCount != 0){
            FEN += to_string(noPieceCount);
            noPieceCount = 0;
        }
        FEN += "/";
    }
    //Hvem sin tur det er
    if(board.turn == 1){
        FEN += " w";
    }
    else{
        FEN += " b";
    }
    //Fiks med castle her
    string oldCastles = getCastlefromFEN(history.back().FEN);
    string newCastles1;
    if(mt == MoveType::CASTLE){
        for(const char& type : oldCastles){
            if(type != history.back().castleType){
                newCastles1 += type;
            }
        }
    }
    else{
        newCastles1 = oldCastles;
    }
    int pieceTypeLastMoved = board.the_board[cordToPoint(history.back().to).x][cordToPoint(history.back().to).y]->getPieceType();
    string newCastles2 = "";
    if(pieceTypeLastMoved == 10){
        if(board.turn == -1){ //det vil si hvit konge siden trekket allerede er gjort
            for(const char& type : oldCastles){
                if(type > 100){ //det vil si k eller q
                    newCastles2 += type;
                }
            }
        }
        else{//altså om det var sort konge som flytta
            for(const char& type : oldCastles){
                if(type < 100){ //det vil si K eller Q
                    newCastles2 += type;
                }
            }
        }
    }
    else{
        newCastles2 += newCastles1;
    }
    string newCastles3 = " ";
    if(pieceTypeLastMoved == 5 and board.the_board[cordToPoint(history.back().to).x][cordToPoint(history.back().to).y]->side != board.turn){
        for(const char& type : oldCastles){
            if(getCastleCorner(cordToPoint(history.back().from)) != NULL){
                if(type != getCastleCorner(cordToPoint(history.back().from))){
                    newCastles3 += type;
                }
            }
        }
    }
    else{
        newCastles3 += newCastles2;
    }
    if(newCastles3.length() == 1){
        newCastles3 += "-";
    }
    FEN += newCastles3;



    //En Passant
    if(board.GetEnPassant().y != NULL){
        //cout << pointToCord(board.GetEnPassant()) << endl;
        FEN += " " + pointToCord(board.GetEnPassant());
    }
    else{
        FEN += " -";
    }
    //Halfmoves
    
    if(mt == MoveType::CAPTURE or mt == MoveType::PAWNPUSH or mt == MoveType::PROMOTION){
        FEN += " 0";
        halfMoves = 0;
    }
    else{
        halfMoves += 1;
        FEN += " " + to_string(halfMoves);
    }
    //TotMove (nr)
    if(board.turn == 1){
        totMoves += 1;
    }
    FEN += " " + to_string(totMoves);
}

void Game::undoMove(){
    TDT4102::Point movedFrom = cordToPoint(history.back().from);
    TDT4102::Point movedTo = cordToPoint(history.back().to);
    char capturedPiece = history.back().capturedPiece;
    MoveType moveType = history.back().moveType;
    TDT4102::Point capturedCord;

    halfMoves = getHMfromFEN(history.back().FEN);
   
    totMoves = getTMfromFEN(history.back().FEN);
    // cout << static_cast<std::underlying_type<MoveType>::type>(moveType) << endl;
    // cout << history.back().from << "->" << history.back().to << endl; 
    if(moveType == MoveType::CAPTURE){
        capturedCord = movedTo; 
    }
    else if(moveType == MoveType::ENPASSANT){
        capturedCord = cordToPoint(history.back().capturedPawnCord);
    }
    else if(moveType == MoveType::CASTLE){  
        char type = history.back().castleType;
        board.moveUndoCastle(type);
    }
    else if(moveType == MoveType::PROMOTION){
        delete board.the_board[movedTo.x][movedTo.y];
        board.the_board[movedTo.x][movedTo.y] = new Pawn(getTurnfromFEN(history.back().FEN));
    }

    board.Move(movedTo, movedFrom);
    board.en_passant = TDT4102::Point(0,0);//hvis denne ikke er her er En-Passant mot seg selv lov

    if(moveType == MoveType::CAPTURE or moveType == MoveType::ENPASSANT){
        board.PlacePieceAt(capturedPiece, capturedCord); 
        
    }
    else if(moveType == MoveType::PROMOTION){
        if(capturedPiece != NULL){
            //cout << pointToCord(movedTo) << endl;
            board.PlacePieceAt(capturedPiece, movedTo);
        }
    }
    if(moveType == MoveType::ENPASSANT){
        board.en_passant = cordToPoint(getEPfromFEN(history.back().FEN));
    }


    FEN = history.back().FEN;
    board.FEN = FEN;
    forwardHistory.push_back(history.back());
    history.pop_back();
}

void Game::forwardMove(){
    TDT4102::Point movedFrom = cordToPoint(forwardHistory.back().from); 
    TDT4102::Point movedTo = cordToPoint(forwardHistory.back().to);
    MoveType moveType = forwardHistory.back().moveType;
    TDT4102::Point capturedCord; 

    halfMoves = getHMfromFEN(forwardHistory.back().FEN); 
    totMoves = getTMfromFEN(forwardHistory.back().FEN); 

    if(moveType == MoveType::CAPTURE){
        capturedCord = movedTo; 
    }
    else if(moveType == MoveType::ENPASSANT){
        capturedCord = cordToPoint(forwardHistory.back().capturedPawnCord);
    }
    else if(moveType == MoveType::CASTLE){  
        char type = forwardHistory.back().castleType;
        board.moveCastle(type);
    }
    else if(moveType == MoveType::PROMOTION){
        char type = forwardHistory.back().promotionType;
        board.forwardPromotion(type, movedFrom);
        if(board.the_board[movedTo.x][movedTo.y] != nullptr){
            delete board.the_board[movedTo.x][movedTo.y];
            board.the_board[movedTo.x][movedTo.y] = nullptr;
        }
    }
    if(moveType == MoveType::CAPTURE or moveType == MoveType::ENPASSANT){
        halfMoves = 0;
        delete board.the_board[capturedCord.x][capturedCord.y];
        board.the_board[capturedCord.x][capturedCord.y] = nullptr;
    }
    
    if(moveType == MoveType::PAWNPUSH and abs(movedFrom.y-movedTo.y) == 2){
        if(board.turn == 1){
            board.en_passant.x = movedFrom.x;
            board.en_passant.y = movedFrom.y - 1;  
        }
        else{
            board.en_passant.x = movedFrom.x;
            board.en_passant.y = movedFrom.y + 1;  
        }
    }

    if(moveType == MoveType::ENPASSANT){
        generateFEN(); //for å lagre riktig en passant
    }
    board.FEN = FEN;
    history.push_back(forwardHistory.back());
    forwardHistory.pop_back();

    board.Move(movedFrom, movedTo);
    generateFEN(); //det brettet faktisk er nå
    board.FEN = FEN;
}

bool Game::checkForMate(int turn) const{
    TDT4102::Point kingPos = board.getKingCord(turn);
    if(board.filterLegalMoves(kingPos).size() == 0 and board.isInCheck(turn, board.getKingCord(turn))){
        return true;
    }
    return false;
}

bool Game::checkForStaleMate(int turn) const{
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            if(board.the_board[x][y] != nullptr){    
                if(board.the_board[x][y]->side == turn){
                    if(board.filterLegalMoves(TDT4102::Point(x,y)).size() != 0){
                        return false;
                    } 
                }
            }
        }
    }
    return true;
}

bool Game::checkForThreeMoveRepitition() const{
    vector<string> FENposes;
    int repCount = 0;
    for(int i = 0; i < history.size(); i++){
        FENposes.push_back(getBoardPosfromFEN(history.at(i).FEN));
    }
    FENposes.push_back(getBoardPosfromFEN(FEN));
    for(int i = 0; i < history.size(); i++){
        string FENPos = FENposes.at(i);
        for(const string& element : FENposes){
            if(element == FENPos){
                repCount += 1;
                if(repCount == 3){
                    return true;
                }
            }
        }
        repCount = 0;
    }
    return false;    
}


