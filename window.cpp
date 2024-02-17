#include "headerFiles/window.h"


SjakkWindow::SjakkWindow() : AnimationWindow(50, 50, winW, winH, "Sjakk")
{}

void SjakkWindow::drawBoard() {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(((i+j) % 2) == 0){
                draw_rectangle({i*padX, j*padY}, padX, padY, TDT4102::Color(242,225,195));
            }
            else{
                draw_rectangle({i*padX, j*padY}, padX, padY, TDT4102::Color(195,160,130));
            }
        }
    }
}

void SjakkWindow::drawLegalMoves(vector<TDT4102::Point>& legalMoves){
    for(const auto& move : legalMoves){
        if(((move.x/padX + move.y/padY) % 2) == 0){
            draw_rectangle(move, padX, padY, TDT4102::Color(249, 240, 123));
        }
        else{
            draw_rectangle(move, padX, padY, TDT4102::Color(226, 207, 89));
        }
    }
}

void SjakkWindow::drawPieces() {
    for(int i = 0; i < pieces.size(); i++){
        draw_image(pieces[i]->coordinate, pieces[i]->sprite, winW/8, winH/8);
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
        pieces.push_back(new Pawn(i*padX,1*padY,-1));
    }

    //White pawns
    for(int i = 0; i < 8; i++){
        pieces.push_back(new Pawn(i*padX,6*padY,1));
    }
    //Tårn
    pieces.push_back(new Rook(0*padX, 0*padY, -1));
    pieces.push_back(new Rook(7*padX, 0*padY, -1));
    pieces.push_back(new Rook(0*padX, 7*padY, 1));
    pieces.push_back(new Rook(7*padX, 7*padY, 1));
    //Løper
    pieces.push_back(new Bishop(2*padX, 0*padY, -1));
    pieces.push_back(new Bishop(5*padX, 0*padY, -1));
    pieces.push_back(new Bishop(2*padX, 7*padY, 1));
    pieces.push_back(new Bishop(5*padX, 7*padY, 1));
    //Hest
    pieces.push_back(new Horse(1*padX, 0*padY, -1));
    pieces.push_back(new Horse(6*padX, 0*padY, -1));
    pieces.push_back(new Horse(1*padX, 7*padY, 1));
    pieces.push_back(new Horse(6*padX, 7*padY, 1));
    //Konge
    pieces.push_back(new King(4*padX, 0*padY, -1));
    pieces.push_back(new King(4*padX, 7*padY, 1));
    //Dronning
    pieces.push_back(new Queen(3*padX, 0*padY, -1));
    pieces.push_back(new Queen(3*padX, 7*padY, 1));


    for(int i = 0; i < pieces.size(); i++){
        string path = pieces[i]->getBasePath();
        TDT4102::Image image{path};
        pieces[i]->sprite = image;
    }

}

void SjakkWindow::movepiece() {
    while(!should_close()){
        drawBoard();
        drawPieces();
        Point mouseCord = get_mouse_coordinates();
        bool mouseClick = is_left_mouse_button_down();
        bool wasMoveLegal = false;

        generateMap(map);


        for(int i = 0; i < pieces.size(); i++){
            int pcx = pieces[i]->coordinate.x;
            int pcy = pieces[i]->coordinate.y;
            if(mouseClick and (mouseCord.x > (pcx-5)) and (mouseCord.x < (pcx + padX+5)) and (mouseCord.y > pcy-5) and (mouseCord.y < (pcy + padY+5))){
                pieces[i]->isActive = true;
                vector<TDT4102::Point> legalMoves = getLegalMoves(pieces[i], map);
                while(!is_right_mouse_button_down()){
                    drawBoard();
                    drawLegalMoves(legalMoves);
                    drawPieces();
                    mouseCord = get_mouse_coordinates();
                    pieces[i]->coordinate.x = mouseCord.x-(padX/2);//(mouseCord.x + 50)/100 * 100;
                    pieces[i]->coordinate.y = mouseCord.y-(padX/2);//(mouseCord.y + 50)/100 * 100;
                    next_frame();
                }
                pieces[i]->isActive = false;

                //Sjekker om trekket var lovlig
                pieces[i]->coordinate.x = (pieces[i]->coordinate.x + (padX/2)) / (winW/8) * (winW/8);
                pieces[i]->coordinate.y = (pieces[i]->coordinate.y + (padX/2)) / (winH/8) * (winH/8);
                //Setter wasMoveLegal til true om det var lovlig
                for(const auto& move : legalMoves){
                    if(pieces[i]->coordinate.x == move.x and pieces[i]->coordinate.y == move.y){
                        wasMoveLegal = true;
                        break;
                    }
                }
                //Resetter pos til piece om ikke
                if(!wasMoveLegal){
                    pieces[i]->coordinate.x = pcx;
                    pieces[i]->coordinate.y = pcy;
                }
                else{wasMoveLegal = false;}

                //Fikser om en brikke blir tatt
                for(int j = 0; j < pieces.size(); j++){
                    if((pieces[i]->coordinate.x == pieces[j]->coordinate.x) and (pieces[i]->coordinate.y == pieces[j]->coordinate.y) and (i != j)){
                        delete pieces[j];
                        pieces.erase(pieces.begin()+j);
                        break;
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
        map[piece->coordinate.x/padX][piece->coordinate.y/padY] = piece->getPieceType() * (piece->side);
    }

}



