#include "headerFiles/game.h"

Game::Game(): gamestate{"active"}, board{Board{}}, win{SjakkWindow{}}
{}

void print8x8arr(const int (&arr)[8][8]){
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            cout << arr[x][y] << '\t';
        }
        cout << endl;
    }
    cout << endl;
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

void Game::undoMove(){
    __SIZE_TYPE__ lastMoveIndex = history.size()-1;

    Point movedFrom = history.at(lastMoveIndex).at(0);
    Point movedTo = history.at(lastMoveIndex).at(1);

    board.Move(movedTo, movedFrom);
    board.PlacePieceAt(captureHistory.at(captureHistory.size()-1), movedTo);

    forwardHistory.push_back(history.at(lastMoveIndex));
    history.pop_back();
    //history.erase(history.begin()+lastMoveIndex);
    captureForwardHistory.push_back(captureHistory.at(lastMoveIndex));
    captureHistory.pop_back();
    //captureHistory.erase(captureHistory.begin()+lastMoveIndex);
}

void Game::forwardMove(){
    __SIZE_TYPE__ moveIndex = forwardHistory.size()-1;

    TDT4102::Point movedFrom = forwardHistory.at(moveIndex).at(0); 
    TDT4102::Point movedTo = forwardHistory.at(moveIndex).at(1);

    board.Move(movedFrom, movedTo);
    //board.PlacePieceAt(captureForwardHistory.at(moveIndex), movedFrom);

    history.push_back(forwardHistory.at(moveIndex));
    forwardHistory.pop_back();
    //forwardHistory.erase(history.begin()+moveIndex);
    captureHistory.push_back(captureForwardHistory.at(moveIndex));
    captureForwardHistory.pop_back();
    //captureForwardHistory.erase(captureForwardHistory.begin()+moveIndex);
}



void Game::playGame(){
    //selve spillet
    activeSquare = TDT4102::Point(8,8);
    moveTo = TDT4102::Point(8,8);


    bool prevMouseClick = false;

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
        win.drawLegalMoves(legalMoves);
        //win.drawLegalMoves(legalMoves);
        win.drawPieces(board.map);
        win.drawAroundActivePiece(activeSquare);

        //Tegne greiene på høyresida
        win.drawClock(whiteTime, blackTime);
        if(isHistory){win.drawUndo();}
        if(isForwardHistory){win.drawForward();}

        //Sjekker om du trykker på en piece
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

            else if(board.TryToMove(activeSquare, mouseCord)){
                //Legg til move i history
                history.push_back(vector{activeSquare, mouseCord});
                captureHistory.push_back(board.pieceAt(mouseCord));
                //Sletter forwardhistory
                forwardHistory.clear();
                captureForwardHistory.clear();
                //Flytt brikken
                board.Move(activeSquare, mouseCord);
                //Stopp å vise lovlige trekk osv
                moveTo = mouseCord;
                clearActiveSquare();
            }
            else if(board.map[mouseCord.x][mouseCord.y] == 0){}
            else{
                //Bytter aktivert brikke
                activeSquare = mouseCord;
                
                legalMoves = board.filterLegalMoves(activeSquare);
            }
            
        }
        prevMouseClick = currentMouseClick;




        updateTimes();
        win.next_frame();
    }
}
