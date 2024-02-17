#include "headerFiles/window.h"

map<int, TDT4102::Image> typeToSprite{
        {1, whitePawnSprite},
        {3, whiteHorseSprite},
        {4, whiteBishopSprite},
        {5, whiteRookSprite},
        {9, whiteQueenSprite},
        {10, whiteKingSprite},
        {-1, blackPawnSprite},
        {-3, blackHorseSprite},
        {-4, blackBishopSprite},
        {-5, blackRookSprite},
        {-9, blackQueenSprite},
        {-10, blackKingSprite}
    };



SjakkWindow::SjakkWindow() : AnimationWindow(50, 50, winW, winH, "Sjakk")
{}

void SjakkWindow::drawBoard() {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(((i+j) % 2) == 0){
                draw_rectangle({i*padX, j*padY}, padX, padY, TDT4102::Color(242,225,195));// TDT4102::Color(250, 0, 250));//TDT4102::Color(242,225,195));
            }
            else{
                draw_rectangle({i*padX, j*padY}, padX, padY, TDT4102::Color(195,160,130));// TDT4102::Color(150,0,150));//TDT4102::Color(195,160,130));
            }
        }
    }
}

void SjakkWindow::drawLegalMoves(vector<TDT4102::Point>& legalMoves) {
    for(const auto& move : legalMoves){
        if(((move.x + move.y) % 2) == 0){
            draw_rectangle({move.x*padX, move.y*padY}, padX, padY, TDT4102::Color(249, 240, 123));
        }
        else{
            draw_rectangle({move.x*padX, move.y*padY}, padX, padY, TDT4102::Color(226, 207, 89));
        }
    }
}

void SjakkWindow::drawAroundActivePiece(int cordX, int cordY) {
    int width = winW/120;
    draw_rectangle({cordX*padX, cordY*padY}, width, padY, TDT4102::Color::crimson);
    draw_rectangle({cordX*padX+padX-width, cordY*padY}, width, padY, TDT4102::Color::crimson);
    draw_rectangle({cordX*padX, cordY*padY}, padX, width, TDT4102::Color::crimson);
    draw_rectangle({cordX*padX, cordY*padY+padY-width}, padX, width, TDT4102::Color::crimson);
}

void SjakkWindow::drawPieces() {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(map[j][i] != 0){
                draw_image({j*padX, i*padY}, typeToSprite.at(map[j][i]), padX, padY);
            }
        }
    }
    
}

void SjakkWindow::piecesNewSetup() {
    //Tømmer pieces vektoren
    for(const auto& piece : pieces){
        delete piece;
    }
    pieces.clear();

    //Legger til nye brikker
    //Black pawns
    for(int i = 0; i < 8; i++){
        pieces.push_back(new Pawn(i,1,-1));
    }

    //White pawns
    for(int i = 0; i < 8; i++){
        pieces.push_back(new Pawn(i,6,1));
    }
    //Tårn
    pieces.push_back(new Rook(0, 0, -1));
    pieces.push_back(new Rook(7, 0, -1));
    pieces.push_back(new Rook(0, 7, 1));
    pieces.push_back(new Rook(7, 7, 1));
    //Løper
    pieces.push_back(new Bishop(2, 0, -1));
    pieces.push_back(new Bishop(5, 0, -1));
    pieces.push_back(new Bishop(2, 7, 1));
    pieces.push_back(new Bishop(5, 7, 1));
    //Hest
    pieces.push_back(new Horse(1, 0, -1));
    pieces.push_back(new Horse(6, 0, -1));
    pieces.push_back(new Horse(1, 7, 1));
    pieces.push_back(new Horse(6, 7, 1));
    //Konge
    pieces.push_back(new King(4, 0, -1));
    pieces.push_back(new King(4, 7, 1));
    //Dronning
    pieces.push_back(new Queen(3, 0, -1));
    pieces.push_back(new Queen(3, 7, 1));


}

void SjakkWindow::promotion(int pieceNr) {
    int pieceXPos = pieces[pieceNr]->coordinate.x;
    int pieceYPos = pieces[pieceNr]->coordinate.y;
    int pieceSide = pieces[pieceNr]->side;

    //Sletter bonden
    delete pieces[pieceNr];
    pieces.erase(pieces.begin() + pieceNr);

    //Lager ny dronning
    pieces.push_back(new Queen(pieceXPos, pieceYPos, pieceSide));

}

bool SjakkWindow::castleLeft(int pieceNrKing) {
    int color = pieces[pieceNrKing]->side;
    if(map[pieces[pieceNrKing]->coordinate.x-1][pieces[pieceNrKing]->coordinate.y] == 0 
    and map[pieces[pieceNrKing]->coordinate.x-2][pieces[pieceNrKing]->coordinate.y] == 0
    and map[pieces[pieceNrKing]->coordinate.x-3][pieces[pieceNrKing]->coordinate.y] == 0){
        for(const auto& i : pieces){
            if(i->getPieceType() == 5 and i->virginMove and i->coordinate.x == 0 and i->side == pieces[pieceNrKing]->side){
                return true;
            }
        } 
    }
    return false;
}

bool SjakkWindow::castleRight(int pieceNrKing) {
    int color = pieces[pieceNrKing]->side;
    if(map[pieces[pieceNrKing]->coordinate.x+1][pieces[pieceNrKing]->coordinate.y] == 0 
    and map[pieces[pieceNrKing]->coordinate.x+2][pieces[pieceNrKing]->coordinate.y] == 0){
        for(const auto& i : pieces){
            if(i->getPieceType() == 5 and i->virginMove and i->coordinate.x == 7 and i->side == pieces[pieceNrKing]->side){
                return true;
            }
        } 
    }
    return false;
}

void SjakkWindow::movepiece() {
    while(!should_close()){
        generateMap(map);
        drawBoard();
        drawPieces();
        Point mouseCord = get_mouse_coordinates();
        bool mouseClick = is_left_mouse_button_down();
        bool wasMoveLegal = false;

        


        for(int i = 0; i < pieces.size(); i++){
            int pcx = pieces[i]->coordinate.x;
            int pcy = pieces[i]->coordinate.y;
            if(mouseClick and (mouseCord.x > (pcx*padX-5)) and (mouseCord.x < (pcx*padX + padX+5)) and (mouseCord.y > pcy*padY-5) and (mouseCord.y < (pcy*padY + padY+5))){
                pieces[i]->isActive = true;
                bool castleL = false;
                int indexCastleL;
                bool castleR = false;
                int indexCastleR;
                vector<TDT4102::Point> legalMoves = pieces[i]->getLegalMoves(map);

                //sjekker om du kan castle
                if(pieces[i]->getPieceType()==10 and pieces[i]->virginMove){
                    castleL = castleLeft(i);
                    castleR = castleRight(i);
                }
                TDT4102::Point castleCord;
                if(castleL){
                    castleCord.x = pieces[i]->coordinate.x - 2;
                    castleCord.y = pieces[i]->coordinate.y;
                    legalMoves.push_back(castleCord);
                    for(int j = 0; j < pieces.size(); j++){
                        if(pieces[j]->getPieceType() == 5 and pieces[j]->coordinate.x == pieces[i]->coordinate.x-4 and pieces[j]->coordinate.y == pieces[i]->coordinate.y){
                            indexCastleL = j;
                        }
                    }
                }
                if(castleR){
                    castleCord.x = pieces[i]->coordinate.x + 2;
                    castleCord.y = pieces[i]->coordinate.y;
                    legalMoves.push_back(castleCord);
                    for(int j = 0; j < pieces.size(); j++){
                        if(pieces[j]->getPieceType() == 5 and pieces[j]->coordinate.x == pieces[i]->coordinate.x+3 and pieces[j]->coordinate.y == pieces[i]->coordinate.y){
                            indexCastleR = j;
                        }
                    }
                }


                
                //logikk om brikke er trykket på
                while(!is_right_mouse_button_down()){
                    drawBoard();
                    drawAroundActivePiece(pcx, pcy); 
                    drawLegalMoves(legalMoves);
                    drawPieces();
                    mouseCord = get_mouse_coordinates();
                    pieces[i]->coordinate.x = mouseCord.x/padX;
                    pieces[i]->coordinate.y = mouseCord.y/padY;
                    next_frame();
                }
                pieces[i]->isActive = false;


                //Sjekker om trekket var lovlig
                //Setter wasMoveLegal til true om det var lovlig
                for(const auto& move : legalMoves){
                    if(pieces[i]->coordinate.x == move.x and pieces[i]->coordinate.y == move.y){
                        wasMoveLegal = true;
                        //om det var første trekk er ikke de neste et
                        if(pieces[i]->virginMove){
                            pieces[i]->virginMove = false;
                        }
                        break;
                    }
                }
                //Resetter pos til piece om ikke
                if(!wasMoveLegal){
                    pieces[i]->coordinate.x = pcx;
                    pieces[i]->coordinate.y = pcy;
                }
                else{wasMoveLegal = false;}

                //om castle
                if(castleL and (pieces[indexCastleL]->coordinate.x-pieces[i]->coordinate.x) == -2){
                    pieces[indexCastleL]->coordinate.x += 3;
                }
                else if(castleR and (pieces[indexCastleR]->coordinate.x-pieces[i]->coordinate.x == 1)){
                    pieces[indexCastleR]->coordinate.x -= 2;
                }

                //Fikser om en brikke blir tatt
                for(int j = 0; j < pieces.size(); j++){
                    if((pieces[i]->coordinate.x == pieces[j]->coordinate.x) and (pieces[i]->coordinate.y == pieces[j]->coordinate.y) and (i != j)){
                        delete pieces[j];
                        pieces.erase(pieces.begin()+j);
                        break;
                    }
                }


                //Fikser om det er promotion
                if(pieces[i]->getPieceType() == 1){
                    if(pieces[i]->side == 1 and pieces[i]->coordinate.y == 0){
                        promotion(i);
                    }
                    else if(pieces[i]->side == -1 and pieces[i]->coordinate.y == 7){
                        promotion(i);
                    }
                }

            }
        }

        
        next_frame();
    }
}





void SjakkWindow::generateMap(int (&map)[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            map[i][j] = 0;
        }
    }

    for(const auto& piece : pieces){
        map[piece->coordinate.x][piece->coordinate.y] = piece->getPieceType() * (piece->side);
    }

}



