#include "headerFiles/game.h"


void Game::playGame2Player(){
    //selve spillet
    activeSquare = TDT4102::Point(8,8);
    moveTo = TDT4102::Point(8,8);


    bool prevMouseClick = false;

    board.createBoardFromFEN(FEN);

    while(gamestate == "active" and !win.should_close()){
        //ting til å koble sammen win og board osv..
        bool currentMouseClick = win.is_left_mouse_button_down();
        TDT4102::Point mouseCord = win.get_mouse_coordinates();
        mouseCord.x /= padX;
        mouseCord.y /= padY;  
        bool isHistory = history.size() > 0;
        bool isForwardHistory = forwardHistory.size() > 0;
        

        //Faktisk tegne spillet
        board.generateMap();
        win.drawBoard();
        if(history.size() > 0){
            win.drawLastMove(history.back().from, history.back().to);
        }
        win.drawLegalMoves(legalMoves);
        //win.drawLegalMoves(legalMoves);
        win.drawPieces(board.map);
        win.drawAroundActivePiece(activeSquare);

        //Tegne greiene på høyresida
        win.drawClock(whiteTime, blackTime);
        if(isHistory){win.drawUndo();}
        if(isForwardHistory){win.drawForward();}

        //Sjekker om du trykker på noe
        if(currentMouseClick and !prevMouseClick){
            //Sjekker om undoMove
            if(isHistory and mouseCord.x > 7 and mouseCord.x < 9 and mouseCord.y > 1 and mouseCord.y < 3){
                undoMove();
                clearActiveSquare();
            }
            //Sjekker om ForwardMove
            if(isForwardHistory and mouseCord.x > 8 and mouseCord.x < 10 and mouseCord.y > 1 and mouseCord.y < 3){
                forwardMove();
                clearActiveSquare();
            }
            else if(mouseCord.x > 7 or mouseCord.y > 7){}

            //Sjekker om man flyttet til et lovlig sted
            else if(board.TryToMoveFiltered(activeSquare, mouseCord) and gameOver == false){
                //Legg til move i history
                if(board.the_board[activeSquare.x][activeSquare.y]->getPieceType()== 1 and (mouseCord.y == 0 or mouseCord.y == 7)){
                    char promotionType = 'q'; //Liten bokstav på denne, nå kan man kun promote til queen, må finne en lur måte å få q,r,b eller n som input, uten å bruke GUI? så når jeg lager en bot slipper jeg å faktisk lage en fysisk robot som må trykke på skjærmen
                    char captureType = NULL;
                    if(board.the_board[mouseCord.x][mouseCord.y] != nullptr){
                        captureType = intToPieceType(-1*board.turn*board.the_board[mouseCord.x][mouseCord.y]->getPieceType());
                    }
                    if(board.turn == 1){
                        promotionType -= 32;
                    }
                    MoveData theMove(FEN, activeSquare, mouseCord, promotionType, captureType, MoveType::PROMOTION);
                    // cout << static_cast<std::underlying_type<MoveType>::type>(theMove.promotionType) << endl;
                    history.push_back(theMove);
                    board.forwardPromotion(promotionType, activeSquare);}
                else if(board.the_board[activeSquare.x][activeSquare.y]->getPieceType() == 1 and abs(mouseCord.x-activeSquare.x)==1 and board.GetEnPassant() == mouseCord){
                    MoveData theMove(FEN, activeSquare, mouseCord, intToPieceType(-board.turn), MoveType::ENPASSANT);
                    history.push_back(theMove);
                    TDT4102::Point capturedCord = cordToPoint(getCaptureEPfromFEN(FEN));
                    delete board.the_board[capturedCord.x][capturedCord.y];
                    board.the_board[capturedCord.x][capturedCord.y] = nullptr;
                }
                else if(board.the_board[activeSquare.x][activeSquare.y]->getPieceType()== 1 and board.the_board[mouseCord.x][mouseCord.y] == nullptr){
                    MoveData theMove(FEN, activeSquare, mouseCord, MoveType::PAWNPUSH);
                    history.push_back(theMove);
                }
                else if(board.the_board[mouseCord.x][mouseCord.y] != nullptr){
                    char capturePiece = intToPieceType(-1*board.turn*board.the_board[mouseCord.x][mouseCord.y]->getPieceType());
                    MoveData theMove(FEN, activeSquare, mouseCord, capturePiece, MoveType::CAPTURE);
                    history.push_back(theMove);
                    delete board.the_board[mouseCord.x][mouseCord.y]; 
                }
                else if(board.the_board[activeSquare.x][activeSquare.y]->getPieceType() == 10 and abs(activeSquare.x - mouseCord.x) == 2){
                    char castleType = getCastleType(mouseCord);
                    MoveData theMove(FEN, activeSquare, castleType, MoveType::CASTLE);
                    history.push_back(theMove);
                    board.moveCastle(castleType);
                }
                else{
                    MoveData theMove(FEN, activeSquare, mouseCord, MoveType::NORMAL);
                    history.push_back(theMove);
                }

                
                //Sletter forwardhistory
                forwardHistory.clear();

                board.Move(activeSquare, mouseCord);                
                //Oppdater FEN-map
                generateFEN();
                board.FEN = FEN;
                // cout << FEN << '\t' << "(game::playgame)" <<endl;
                //Stopp å vise lovlige trekk osv
                moveTo = mouseCord;
                clearActiveSquare();



                if(checkForMate(board.turn) or checkForStaleMate(board.turn) or getHMfromFEN(FEN) >= 100 or checkForThreeMoveRepitition()){
                    gameOver = true;
                }
                if(gameOver){
                    if(checkForMate(1)){
                        cout << "Checkmate! Black won!" << endl;
                    }
                    else if(checkForMate(-1)){
                        cout << "Checkmate! White won!" << endl;
                    }
                    else if(checkForStaleMate(board.turn)){
                        cout << "Stalemate! Its a draw!" << endl;
                    }
                    else if(getHMfromFEN(FEN) >= 100){
                        cout << "50 move rule! Its a draw!" << endl;
                    }
                    else if(checkForThreeMoveRepitition()){
                        cout << "Three move repitition! Its a draw!" << endl;
                    }
                }



            }
            else if(board.the_board[mouseCord.x][mouseCord.y] == nullptr){clearActiveSquare();}
            else{
                //Bytter aktivert brikke
                activeSquare = mouseCord;
                
                legalMoves = board.filterLegalMoves(activeSquare);
            }
            
            
        }
        prevMouseClick = currentMouseClick;
        
        if(!gameOver){
            updateTimes();
        }
        win.next_frame();
    }
}

