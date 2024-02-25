#include "headerFiles/board.h"

Board::Board(): en_passant{NULL}, turn{1} 
{BoardNewSetup();}



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
    //Sjekker om det er en pawn sitt første trekk, og det skal være lovlig med en passant
    if(the_board[from.x][from.y]->getPieceType() == 1 and abs(from.y - to.y) == 2){
        if(from.x == 1){
            TDT4102::Point ep(from.x,from.y+1);
            en_passant = ep;
        }
        else{
            TDT4102::Point ep(from.x,from.y-1);
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

bool Board::TryToMove(TDT4102::Point from, TDT4102::Point to){
    if(0 > from.x or from.x > 7 or 0 > from.y or from.y > 7 or 0 > to.x or to.x > 7 or 0 > to.y or to.y > 7){return false;}
    Piece* piece = the_board[from.x][from.y];
    //Retrun false om du flytter et tomt felt
    if(piece == nullptr){return false;}
    //Sjekker at det er 'din' tur
    if(piece->side != turn){return false;}
    //om trekkene er utenfor brettet
    

    //Sjekker om trekket er lovlig
    generateMap();
    vector<TDT4102::Point> legalMoves = piece->getLegalMoves(map, from);
    for(TDT4102::Point point : legalMoves){
        if(point.x == to.x and point.y == to.y){
            return true;
        }
    }

    return false;

}

// bool Board::isInCheck(int side){
//     TDT4102::Point kingCord;
//     for(int y = 0; y < 8; y++){
//         for(int x = 0; x < 8; x++){
//             if(the_board[x][y]->getPieceType() == 10){
//                 if(the_board[x][y]->side == side){
//                     kingCord.x = x;
//                     kingCord.y = y;
//                 }
//             }
//         }
//     }
//     cout << kingCord.x << ", " << kingCord.y << endl;
//     for(int y = 0; y < 8; y++){
//         for(int x = 0; x < 8; x++){
//             Piece* tempPiece = the_board[x][y];
//             if(tempPiece != nullptr and tempPiece->side != side){
//                 vector<TDT4102::Point> moves = tempPiece->getLegalMoves(map, TDT4102::Point(x,y));
//                 for(const auto& cord : moves){
//                     if(cord.x == kingCord.x and cord.y == kingCord.y){
//                         return true;
//                     }
//                 }
//             }
//         }
        
//     }
//     return false;
// }

Piece* Board::pieceAt(TDT4102::Point point){
    return the_board[point.x][point.y];
}

void Board::PlacePieceAt(Piece* piece, TDT4102::Point point){
    the_board[point.x][point.y] = piece;
}

TDT4102::Point Board::GetEnPassant(){
    return en_passant;
}
