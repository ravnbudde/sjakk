#include "headerFiles/window.h"


SjakkWindow::SjakkWindow() : AnimationWindow(50, 50, winW, winH, "Sjakk")
{}

void SjakkWindow::drawBoard() {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(((i+j) % 2) == 0){
                draw_rectangle({i*padX, j*padY}, padX, padY, TDT4102::Color::white_smoke);
            }
            else{
                draw_rectangle({i*padX, j*padY}, padX, padY, TDT4102::Color::dark_slategray);
            }
        }
    }

    drawPieces();

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
        pieces.push_back(new Pawn(i*padX,1*padY,0));
    }

    //White pawns
    for(int i = 0; i < 8; i++){
        pieces.push_back(new Pawn(i*padX,6*padY,1));
    }
    //Tårn
    pieces.push_back(new Rook(0*padX, 0*padY, 0));
    pieces.push_back(new Rook(7*padX, 0*padY, 0));
    pieces.push_back(new Rook(0*padX, 7*padY, 1));
    pieces.push_back(new Rook(7*padX, 7*padY, 1));
    //Løper
    pieces.push_back(new Bishop(2*padX, 0*padY, 0));
    pieces.push_back(new Bishop(5*padX, 0*padY, 0));
    pieces.push_back(new Bishop(2*padX, 7*padY, 1));
    pieces.push_back(new Bishop(5*padX, 7*padY, 1));
    //Hest
    pieces.push_back(new Horse(1*padX, 0*padY, 0));
    pieces.push_back(new Horse(6*padX, 0*padY, 0));
    pieces.push_back(new Horse(1*padX, 7*padY, 1));
    pieces.push_back(new Horse(6*padX, 7*padY, 1));
    //Konge
    pieces.push_back(new King(4*padX, 0*padY, 0));
    pieces.push_back(new King(4*padX, 7*padY, 1));
    //Dronning
    pieces.push_back(new Queen(3*padX, 0*padY, 0));
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
        Point mouseCord = get_mouse_coordinates();
        bool mouseClick = is_left_mouse_button_down();


        for(int i = 0; i < pieces.size(); i++){
            int pcx = pieces[i]->coordinate.x;
            int pcy = pieces[i]->coordinate.y;
            if(mouseClick and (mouseCord.x > (pcx-5)) and (mouseCord.x < (pcx + padX+5)) and (mouseCord.y > pcy-5) and (mouseCord.y < (pcy + padY+5))){
                while(!is_right_mouse_button_down()){
                    drawBoard();
                    mouseCord = get_mouse_coordinates();
                    pieces[i]->coordinate.x = mouseCord.x-(padX/2);//(mouseCord.x + 50)/100 * 100;
                    pieces[i]->coordinate.y = mouseCord.y-(padX/2);//(mouseCord.y + 50)/100 * 100;
                    next_frame();
                }
                pieces[i]->coordinate.x = (pieces[i]->coordinate.x + (padX/2)) / (winW/8) * (winW/8);
                pieces[i]->coordinate.y = (pieces[i]->coordinate.y + (padX/2)) / (winH/8) * (winH/8);

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
