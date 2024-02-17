#include "headerFiles/gameLogicSupport.h"

vector<TDT4102::Point> getLegalMoves(Piece *piece, int (&map)[8][8]) {
    vector<TDT4102::Point> moves;
    TDT4102::Point move;
    
    int pieceType = piece->getPieceType();

    //pawn
    if(pieceType == 1){
        int dy;
        //Hvis sort
        if(piece->side == -1){dy = 1;}
        //Hvis hvit
        else{dy = -1;}


        //Sjekker om du ikke kan gå 2 selv om du burde
        if((!piece->virginMove and piece->coordinate.y==padY) or (!piece->virginMove and piece->coordinate.y==6*padY)){
            piece->virginMove = true;
        }

        //Sjekker om du kan gå rett fram 2 og/eller 1
        if(map[piece->coordinate.x/padX][piece->coordinate.y/padY + dy] == 0){
            move.y = piece->coordinate.y + dy*padY;
            move.x = piece->coordinate.x;
            moves.push_back(move);
            if(piece->virginMove and (map[piece->coordinate.x/padX][piece->coordinate.y/padY + 2*dy] == 0)){
                move.y = piece->coordinate.y +2*dy*padY;
                move.x = piece->coordinate.x;
                moves.push_back(move);
                piece->virginMove = false;
            }
        }


        //Sjekker om du kan ta på skrå
        if(map[piece->coordinate.x/padX-1][piece->coordinate.y/padY + dy]*piece->side < 0){
            move.y = piece->coordinate.y+dy*padY;
            move.x = piece->coordinate.x - padX;
            moves.push_back(move);
        }
        if(map[piece->coordinate.x/padX+1][piece->coordinate.y/padY + dy]*piece->side < 0){
            move.y = piece->coordinate.y+dy*padY;
            move.x = piece->coordinate.x + padX;
            moves.push_back(move);
        }

        return moves;
    }

    //Horse
    else if(pieceType == 3){
        int dy = 2;
        int dx = 2;

       
        //de to ned
        move.y = piece->coordinate.y + dy*padY;
        move.x = piece->coordinate.x + padX;
        if(0 <= move.y/padY and move.y/padY <= 7 and 0 <= move.x/padX and move.x/padX <= 7){
        if(map[move.x/padX][move.y/padY]*piece->side < 1){    
            moves.push_back(move);
        }
        }
        move.x = piece->coordinate.x - padX;
        if(0 <= move.y/padY and move.y/padY <= 7 and 0 <= move.x/padX and move.x/padX <= 7){
        if(map[move.x/padX][move.y/padY]*piece->side < 1){    
            moves.push_back(move);
        }
        }
        //de to opp
        move.y = piece->coordinate.y - dy*padY;
        if(0 <= move.y/padY and move.y/padY <= 7 and 0 <= move.x/padX and move.x/padX <= 7){
        if(map[move.x/padX][move.y/padY]*piece->side < 1){    
            moves.push_back(move);
        }
        }
        move.x = piece->coordinate.x + padX;
        if(0 <= move.y/padY and move.y/padY <= 7 and 0 <= move.x/padX and move.x/padX <= 7){
        if(map[move.x/padX][move.y/padY]*piece->side < 1){    
            moves.push_back(move);
        }
        }
        //de to høyre
        move.x = piece->coordinate.x +dx*padX;
        move.y = piece->coordinate.y + padY;
        if(0 <= move.y/padY and move.y/padY <= 7 and 0 <= move.x/padX and move.x/padX <= 7){
        if(map[move.x/padX][move.y/padY]*piece->side < 1){    
            moves.push_back(move);
        }
        }
        move.y = piece->coordinate.y - padY;
        if(0 <= move.y/padY and move.y/padY <= 7 and 0 <= move.x/padX and move.x/padX <= 7){
        if(map[move.x/padX][move.y/padY]*piece->side < 1){    
            moves.push_back(move);
        }
        }
        //de to venstre
        move.x = piece->coordinate.x - dx*padX;
        if(0 <= move.y/padY and move.y/padY <= 7 and 0 <= move.x/padX and move.x/padX <= 7){
        if(map[move.x/padX][move.y/padY]*piece->side < 1){    
            moves.push_back(move);
        }
        }
        move.y = piece->coordinate.y + padY;
        if(0 <= move.y/padY and move.y/padY <= 7 and 0 <= move.x/padX and move.x/padX <= 7){
        if(map[move.x/padX][move.y/padY]*piece->side < 1){    
            moves.push_back(move);
        }
        }

        return moves;
    }

    //bishop
    else if(pieceType == 4){
        move.x = piece->coordinate.x;
        move.y = piece->coordinate.y;
        //Opp til venstre
        while(move.y > -1){
            move.x -= padX;
            move.y -= padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }
        //opp til høyre
        move.x = piece->coordinate.x;
        move.y = piece->coordinate.y;
        while(move.y > -1){
            move.x += padX;
            move.y -= padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }

        //ned til venstre
        move.x = piece->coordinate.x;
        move.y = piece->coordinate.y;
        while(move.y < 8*padY + 1){
            move.x -= padX;
            move.y += padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }

        //ned til høyre
        move.x = piece->coordinate.x;
        move.y = piece->coordinate.y;
        while(move.y < 8*padY+1){
            move.x += padX;
            move.y += padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }


        return moves;
    }

    //rook
    else if(pieceType == 5){
        move.x = piece->coordinate.x;
        move.y = piece->coordinate.y;
        //opp
        while(move.y > -1){
            move.y -= padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }
        //ned
        move.y = piece->coordinate.y;
        while(move.y < 8*padY+1){
            move.y += padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }

        //venstre
        move.y = piece->coordinate.y;
        while(move.x > -1){
            move.x -= padX;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }

        //høyre
        move.x = piece->coordinate.x;
        while(move.x < 8*padX+1){
            move.x += padX;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }


        return moves;
    }

    //queen
    else if(pieceType == 9){
        move.x = piece->coordinate.x;
        move.y = piece->coordinate.y;
        //Opp til venstre
        while(move.y > -1){
            move.x -= padX;
            move.y -= padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }
        //opp til høyre
        move.x = piece->coordinate.x;
        move.y = piece->coordinate.y;
        while(move.y > -1){
            move.x += padX;
            move.y -= padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }
        //ned til venstre
        move.x = piece->coordinate.x;
        move.y = piece->coordinate.y;
        while(move.y < 8*padY + 1){
            move.x -= padX;
            move.y += padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }
        //ned til høyre
        move.x = piece->coordinate.x;
        move.y = piece->coordinate.y;
        while(move.y < 8*padY+1){
            move.x += padX;
            move.y += padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }
        move.x = piece->coordinate.x;
        move.y = piece->coordinate.y;
        //opp
        while(move.y > -1){
            move.y -= padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }
        //ned
        move.y = piece->coordinate.y;
        while(move.y < 8*padY+1){
            move.y += padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }
        //venstre
        move.y = piece->coordinate.y;
        while(move.x > -1){
            move.x -= padX;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }
        //høyre
        move.x = piece->coordinate.x;
        while(move.x < 8*padX+1){
            move.x += padX;
            if(map[move.x/padX][move.y/padY]*piece->side < 0){    
                moves.push_back(move);
                break;
            }
            else if(map[move.x/padX][move.y/padY]*piece->side == 0){    
                moves.push_back(move);
            }
            else{break;}
        }

        return moves;
    }

    //king
    else if(pieceType == 10){
        move.x = piece->coordinate.x;
        move.y = piece->coordinate.y;

        for(int i = -1; i < 2; i++){
            move.x = piece->coordinate.x + i*padX;
            move.y = piece->coordinate.y - padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 1){    
                moves.push_back(move);
            }
            if(i!=0){
                move.y = piece->coordinate.y;
                if(map[move.x/padX][move.y/padY]*piece->side < 1){    
                    moves.push_back(move);
                }
            }
            move.y = piece->coordinate.y + padY;
            if(map[move.x/padX][move.y/padY]*piece->side < 1){    
                moves.push_back(move);
            }
        }
       
        return moves;
    }


    else{return moves;}


    
    
    

}






