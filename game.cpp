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

void Game::undoMove(){
    int lastMoveIndex = history.size()-1;

    Point movedFrom = history.at(lastMoveIndex).at(0);
    Point movedTo = history.at(lastMoveIndex).at(1);

    board.Move(movedTo, movedFrom);
    board.PlacePieceAt(captureHistory.at(captureHistory.size()-1), movedTo);

    forwardHistory.push_back(history.at(lastMoveIndex));
    history.erase(history.begin()+lastMoveIndex);
    captureForwardHistory.push_back(captureHistory.at(lastMoveIndex));
    captureHistory.erase(captureHistory.begin()+lastMoveIndex);
}

void Game::forwardMove(){
    int moveIndex = forwardHistory.size()-1;

    TDT4102::Point movedFrom = forwardHistory.at(moveIndex).at(0); 
    TDT4102::Point movedTo = forwardHistory.at(moveIndex).at(1);

    board.Move(movedFrom, movedTo);
    //board.PlacePieceAt(captureForwardHistory.at(moveIndex), movedFrom);

    history.push_back(forwardHistory.at(moveIndex));
    forwardHistory.erase(history.begin()+moveIndex);
    captureHistory.push_back(captureForwardHistory.at(moveIndex));
    captureForwardHistory.erase(captureForwardHistory.begin()+moveIndex);
}


vector<TDT4102::Point> Game::getLegalMoves(TDT4102::Point activeSquare){
    //Henter alle pseudolovlige trekk til brikken
    vector<TDT4102::Point> pseudoLegalMoves = board.the_board[activeSquare.x][activeSquare.y]->getLegalMoves(board.map, activeSquare);
    int color = board.the_board[activeSquare.x][activeSquare.y]->side;
    vector<TDT4102::Point>legalMoves;

    //Lage en kopi av brettet i funksjonen. tror det er her det blir noe feil?
    Board tempBoard{};
    tempBoard.turn = board.turn;
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            //tempBoard.the_board[x][y] = board.the_board[x][y];
            if(board.the_board[x][y] == nullptr){
                tempBoard.the_board[x][y] = nullptr;
                //cout << 0 << '\t';
            }
            else if(board.the_board[x][y]->getPieceType() == 1){
                tempBoard.the_board[x][y] = new Pawn(board.the_board[x][y]->side);
                //cout << tempBoard.the_board[x][y]->getPieceType()*tempBoard.the_board[x][y]->side << '\t';
            }
            else if(board.the_board[x][y]->getPieceType() == 3){
                tempBoard.the_board[x][y] = new Horse(board.the_board[x][y]->side);
                //cout << tempBoard.the_board[x][y]->getPieceType()*tempBoard.the_board[x][y]->side << '\t';
            }
            else if(board.the_board[x][y]->getPieceType() == 4){
                tempBoard.the_board[x][y] = new Bishop(board.the_board[x][y]->side);
                //cout << tempBoard.the_board[x][y]->getPieceType()*tempBoard.the_board[x][y]->side << '\t';
            }
            else if(board.the_board[x][y]->getPieceType() == 5){
                tempBoard.the_board[x][y] = new Rook(board.the_board[x][y]->side);
                //cout << tempBoard.the_board[x][y]->getPieceType()*tempBoard.the_board[x][y]->side << '\t';
            }
            else if(board.the_board[x][y]->getPieceType() == 9){
                tempBoard.the_board[x][y] = new Queen(board.the_board[x][y]->side);
                //cout << tempBoard.the_board[x][y]->getPieceType()*tempBoard.the_board[x][y]->side << '\t';
            }
            else if(board.the_board[x][y]->getPieceType() == 10){
                tempBoard.the_board[x][y] = new King(board.the_board[x][y]->side);
                //cout << tempBoard.the_board[x][y]->getPieceType()*tempBoard.the_board[x][y]->side << '\t';
            }
            else{
                tempBoard.the_board[x][y] = nullptr;
                //cout << 0 << '\t';
            }
        }
        //cout << endl;
    }

    

    //ser på brikken vi skal sjekke
    Piece* piece = tempBoard.the_board[activeSquare.x][activeSquare.y];
    //om det ikke er en brikke return tom vektor
    if(piece == nullptr){return pseudoLegalMoves;}



    for(int i = 0; i < pseudoLegalMoves.size(); i++){
        tempBoard.generateMap();
            //returnerer bare true på firkanter 1 unna brikka
        if(tempBoard.TryToMove(activeSquare,pseudoLegalMoves.at(i))){

            
            //print8x8arr(tempBoard.map);
            tempBoard.Move(activeSquare, pseudoLegalMoves.at(i));
            tempBoard.generateMap();

                
            if(!tempBoard.isInCheck(color)){
                legalMoves.push_back(pseudoLegalMoves.at(i));
            }

            tempBoard.Move(pseudoLegalMoves.at(i), activeSquare);
        }
    }

    //tempboard slettes av seg selv når man går ut av funksjonen    
    
    return legalMoves;
}

void Game::playGame(){
    //selve spillet
    TDT4102::Point activeSquare(8,8);
    TDT4102::Point moveTo(8,8);
    vector<TDT4102::Point> legalMoves;
    vector<TDT4102::Point> legalMovescheck;


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
        win.drawLegalMoves(legalMovescheck);
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
            }
            //Sjekker om ForwardMove
            if(isForwardHistory and mouseCord.x > 8 and mouseCord.x < 10 and mouseCord.y > 1 and mouseCord.y < 3){
                forwardMove();
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
                activeSquare = TDT4102::Point(8,8);
                legalMoves.clear();
                //cout << true << endl;
                cout << board.isInCheck(board.the_board[mouseCord.x][mouseCord.y]->side*(-1)) << endl;
            }
            else if(board.map[mouseCord.x][mouseCord.y] == 0){
                //Stopp å vise lovlige trekk osv..
                activeSquare = TDT4102::Point(8,8);
                legalMoves.clear();
            }
            else{
                //Bytter aktivert brikke
                activeSquare = mouseCord;
                
                //legalMoves = getLegalMoves(activeSquare);
                legalMovescheck = getLegalMoves(activeSquare);
                legalMoves = board.the_board[activeSquare.x][activeSquare.y]->getLegalMoves(board.map, activeSquare); //getLegalMoves(activeSquare);    
            }
        }
        prevMouseClick = currentMouseClick;




        updateTimes();
        win.next_frame();
    }
}
