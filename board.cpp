#include "headerFiles/board.h"

Board::Board(): en_passant{TDT4102::Point(NULL, NULL)}, turn{1} 
{BoardNewSetup();}

Board::~Board()
{
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            delete the_board[x][y];
            the_board[x][y] = nullptr;
        }
    } 
}


void Board::BoardNewSetup(){

    //nye brikker
    //pawns
    for(int i = 0; i < 8; i++){
        the_board[i][1] = new Pawn(-1); //Black
        the_board[i][6] = new Pawn(1); //White
    }
    //Rooks
    the_board[0][0] = new Rook(-1);
    the_board[7][0] = new Rook(-1);
    the_board[0][7] = new Rook(1);
    the_board[7][7] = new Rook(1);
    //Bishop
    the_board[2][0] = new Bishop(-1);
    the_board[5][0] = new Bishop(-1);
    the_board[2][7] = new Bishop(1);
    the_board[5][7] = new Bishop(1);
    //Horse
    the_board[1][0] = new Horse(-1);
    the_board[6][0] = new Horse(-1);
    the_board[1][7] = new Horse(1);
    the_board[6][7] = new Horse(1);
    //King
    the_board[4][0] = new King(-1);
    the_board[4][7] = new King(1);
    //Queen
    the_board[3][0] = new Queen(-1);
    the_board[3][7] = new Queen(1);

    //Tomme felt
    for(int x = 0; x < 8; x++){
        for(int y = 2; y < 6; y++){
            the_board[x][y] = nullptr;
        }
    }

}

void Board::generateMap(){
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            if(the_board[x][y] != nullptr){
                map[x][y] = the_board[x][y]->getPieceType()*the_board[x][y]->side;
            }
            else{
                map[x][y] = 0;
            }
        }
    }    
}

void Board::Move(TDT4102::Point from, TDT4102::Point to){
    //gjør ikkeno om trekk er utenfor brettet
    if(from.x > 7 or from.x<0 or from.y>7 or from.y<0 or to.x>7 or to.x<0 or to.y>7 or to.y<0)
        return;
    //Sjekker om det er en pawn sitt første trekk, og det skal være lovlig med en passant
    if(the_board[from.x][from.y]->getPieceType() == 1 and abs(from.y - to.y) == 2){
        if(turn == 1){
            TDT4102::Point ep(from.x,from.y-1);
            en_passant = ep;
        }
        else{
            TDT4102::Point ep(from.x,from.y+1);
            en_passant = ep;
        }
    }
    else{en_passant = TDT4102::Point(NULL, NULL);}

    //Flytter brikka
    the_board[to.x][to.y] = the_board[from.x][from.y];
    the_board[from.x][from.y] = nullptr;

    //Bytter turn
    if(turn == 1){
        turn = -1;
    }
    else{turn = 1;}
}

bool Board::TryToMove(TDT4102::Point from, TDT4102::Point to) const{
    //om trekkene er utenfor brettet
    if(0 > from.x or from.x > 7 or 0 > from.y or from.y > 7 or 0 > to.x or to.x > 7 or 0 > to.y or to.y > 7){return false;}
    Piece* piece = the_board[from.x][from.y];
    //Retrun false om du flytter et tomt felt
    if(piece == nullptr){return false;}
    //Sjekker at det er 'din' tur
    if(piece->side != turn){return false;}
    
    

    //Sjekker om trekket er lovlig;
    vector<TDT4102::Point> legalMoves = piece->getLegalMoves(map, from);
    if(checkEnPassant(from)){
        legalMoves.push_back(GetEnPassant());
    }

    for(TDT4102::Point point : legalMoves){
        if(point.x == to.x and point.y == to.y){
            return true;
        }
    }

    return false;

}

bool Board::TryToMoveFiltered(TDT4102::Point from, TDT4102::Point to) const{
    //om trekkene er utenfor brettet
    if(0 > from.x or from.x > 7 or 0 > from.y or from.y > 7 or 0 > to.x or to.x > 7 or 0 > to.y or to.y > 7){return false;}
    Piece* piece = the_board[from.x][from.y];
    //Retrun false om du flytter et tomt felt
    if(piece == nullptr){return false;}
    //Sjekker at det er 'din' tur
    if(piece->side != turn){return false;}
    
    

    //Sjekker om trekket er lovlig;
    vector<TDT4102::Point> legalMoves = filterLegalMoves(from);
    for(TDT4102::Point point : legalMoves){
        if(point.x == to.x and point.y == to.y){
            return true;
        }
    }

    return false;

}

bool Board::isInCheck(int side) const{
    TDT4102::Point kingCord;
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            if(the_board[x][y] != nullptr){    
                if(the_board[x][y]->getPieceType() == 10){
                    if(the_board[x][y]->side == side){
                        kingCord.x = x;
                        kingCord.y = y;
                    }
                }
            }
        }
    }

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            Piece* tempPiece = the_board[x][y];
            if(tempPiece != nullptr and tempPiece->side != side){
                vector<TDT4102::Point> moves = tempPiece->getLegalMoves(map, TDT4102::Point(x,y));
                for(const auto& cord : moves){
                    if(cord.x == kingCord.x and cord.y == kingCord.y){
                        return true;
                    }
                }
            }
        }
        
    }
    return false;
}

Piece* Board::pieceAt(TDT4102::Point point){
    return the_board[point.x][point.y];
}

void Board::PlacePieceAt(const char piece, TDT4102::Point point){
    switch (piece)
    {
    case 'P':
        the_board[point.x][point.y] = new Pawn(1);
        break;
    case 'H':
        the_board[point.x][point.y] = new Horse(1);
        break;
    case 'B':
        the_board[point.x][point.y] = new Bishop(1);
        break;
    case 'R':
        the_board[point.x][point.y] = new Rook(1);
        break;
    case 'Q':
        the_board[point.x][point.y] = new Queen(1);
        break;
    case 'K':
        the_board[point.x][point.y] = new King(1);
        break;
    case 'p':
        the_board[point.x][point.y] = new Pawn(-1);
        break;
    case 'h':
        the_board[point.x][point.y] = new Horse(-1);
        break;
    case 'b':
        the_board[point.x][point.y] = new Bishop(-1);
        break;
    case 'r':
        the_board[point.x][point.y] = new Rook(-1);
        break;
    case 'q':
        the_board[point.x][point.y] = new Queen(-1);
        break;
    case 'k':
        the_board[point.x][point.y] = new King(-1);
        break;   
    
    default:
        the_board[point.x][point.y] = nullptr;
        cout << "Placed zeroptr in Board::PlacePieceAt" << endl;
        break;
    } 
    return;
}

TDT4102::Point Board::GetEnPassant() const{
    return en_passant;
}

vector<TDT4102::Point> Board::filterLegalMoves(TDT4102::Point activeSquare) const{
    //Henter alle pseudolovlige trekk til brikken
    vector<TDT4102::Point> pseudoLegalMoves = the_board[activeSquare.x][activeSquare.y]->getLegalMoves(map, activeSquare);
    int color = the_board[activeSquare.x][activeSquare.y]->side;
    vector<TDT4102::Point>legalMoves;

    //Lage en kopi av brettet i funksjonen. tror det er her det blir noe feil?
    Board tempBoard{};
    tempBoard.turn = turn;
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            //tempBoard.the_board[x][y] = board.the_board[x][y];
            if(the_board[x][y] == nullptr){
                tempBoard.the_board[x][y] = nullptr;
                //cout << 0 << '\t';
            }
            else if(the_board[x][y]->getPieceType() == 1){
                tempBoard.the_board[x][y] = new Pawn(the_board[x][y]->side);
                //cout << tempBoard.the_board[x][y]->getPieceType()*tempBoard.the_board[x][y]->side << '\t';
            }
            else if(the_board[x][y]->getPieceType() == 3){
                tempBoard.the_board[x][y] = new Horse(the_board[x][y]->side);
                //cout << tempBoard.the_board[x][y]->getPieceType()*tempBoard.the_board[x][y]->side << '\t';
            }
            else if(the_board[x][y]->getPieceType() == 4){
                tempBoard.the_board[x][y] = new Bishop(the_board[x][y]->side);
                //cout << tempBoard.the_board[x][y]->getPieceType()*tempBoard.the_board[x][y]->side << '\t';
            }
            else if(the_board[x][y]->getPieceType() == 5){
                tempBoard.the_board[x][y] = new Rook(the_board[x][y]->side);
                //cout << tempBoard.the_board[x][y]->getPieceType()*tempBoard.the_board[x][y]->side << '\t';
            }
            else if(the_board[x][y]->getPieceType() == 9){
                tempBoard.the_board[x][y] = new Queen(the_board[x][y]->side);
                //cout << tempBoard.the_board[x][y]->getPieceType()*tempBoard.the_board[x][y]->side << '\t';
            }
            else if(the_board[x][y]->getPieceType() == 10){
                tempBoard.the_board[x][y] = new King(the_board[x][y]->side);
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

    //sjekker om en-passant er relevant
    if(checkEnPassant(activeSquare)){
        cout << TryToMove(activeSquare, GetEnPassant()) << endl;
        if(TryToMove(activeSquare, GetEnPassant())){
            legalMoves.push_back(GetEnPassant());
        }
    }

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

bool Board::checkEnPassant(TDT4102::Point activeSquare) const{
    //om bonden man ser på er for lang unna uansett return tom
    if(the_board[activeSquare.x][activeSquare.y]->getPieceType()==1 and en_passant.x !=0){
        if((activeSquare.y-en_passant.y)*turn != 1 or abs(activeSquare.x-en_passant.x)*turn != 1){
            return false;
        }

        return true;
    }
    return false;
}

