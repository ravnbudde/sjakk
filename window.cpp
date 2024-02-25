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

void SjakkWindow::drawAroundActivePiece(TDT4102::Point cord) {
    int width = winW/120;
    draw_rectangle({cord.x*padX, cord.y*padY}, width, padY, TDT4102::Color::crimson);
    draw_rectangle({cord.x*padX+padX-width, cord.y*padY}, width, padY, TDT4102::Color::crimson);
    draw_rectangle({cord.x*padX, cord.y*padY}, padX, width, TDT4102::Color::crimson);
    draw_rectangle({cord.x*padX, cord.y*padY+padY-width}, padX, width, TDT4102::Color::crimson);
}

void SjakkWindow::drawPieces(int (&map)[8][8]) {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(map[j][i] != 0){
                draw_image({j*padX, i*padY}, typeToSprite.at(map[j][i]), padX, padY);
            }
        }
    }
    
}

void SjakkWindow::drawClock(int timeWhitems, int timeBlackms){
    int whiteMinutes = timeWhitems/60000;
    timeWhitems = timeWhitems%60000;
    int whiteSeconds = timeWhitems/1000;
    timeWhitems = timeWhitems%1000;
    int whiteDS = timeWhitems/100;
    string whiteTime = to_string(whiteMinutes) + ":" + to_string(whiteSeconds) + "." + to_string(whiteDS);
    int blackMinutes = timeBlackms/60000;
    timeBlackms = timeBlackms%60000;
    int blackSeconds = timeBlackms/1000;
    timeBlackms = timeBlackms%1000;
    int blackDS = timeBlackms/100;
    string blackTime = to_string(blackMinutes) + ":" + to_string(blackSeconds) + "." + to_string(blackDS); 
    //Tegner hvit tid
    draw_rectangle({8*padX, 1*padY}, 2*padX, padY, TDT4102::Color::white_smoke);
    draw_text({8*padX, 1*padY}, whiteTime, TDT4102::Color::black, 75);
    //Tegner sort tid
    draw_rectangle({8*padX, 0*padY}, 2*padX, 1*padY, TDT4102::Color::black);
    draw_text({8*padX, 0*padY}, blackTime, TDT4102::Color::white, 75);
}

void SjakkWindow::drawUndo(){
    draw_rectangle({8*padX, 2*padY}, padX, padY, TDT4102::Color::gray, TDT4102::Color::black);
    draw_triangle({int(8*padX+0.1*padX), int(2*padY+0.5*padY)}, {int(8*padX+0.3*padX), int(2*padY+0.7*padY)}, {int(8*padX+0.3*padX),int(2*padY+0.3*padY)}, TDT4102::Color::black);
    draw_rectangle({int(8*padX+0.3*padX), int(2*padY+0.4*padY)}, 0.6*padX, 0.2*padY, TDT4102::Color::black);
}

void SjakkWindow::drawForward(){
    draw_rectangle({9*padX, 2*padY}, padX, padY, TDT4102::Color::gray, TDT4102::Color::black);
    draw_triangle({int(10*padX-0.1*padX), int(2*padY+0.5*padY)}, {int(10*padX-0.3*padX), int(2*padY+0.7*padY)}, {int(10*padX-0.3*padX),int(2*padY+0.3*padY)}, TDT4102::Color::black);
    draw_rectangle({int(10*padX-0.9*padX), int(2*padY+0.4*padY)}, 0.6*padX, 0.2*padY, TDT4102::Color::black);
}

// void SjakkWindow::movepiece() {
//     while(!should_close()){
//         generateMap(map);
//         drawBoard();
//         drawPieces();
//         Point mouseCord = get_mouse_coordinates();
//         bool mouseClick = is_left_mouse_button_down();
//         bool wasMoveLegal = false;

        


//         for(int i = 0; i < pieces.size(); i++){
//             int pcx = pieces[i]->coordinate.x;
//             int pcy = pieces[i]->coordinate.y;
//             if(mouseClick and (mouseCord.x > (pcx*padX-5)) and (mouseCord.x < (pcx*padX + padX+5)) and (mouseCord.y > pcy*padY-5) and (mouseCord.y < (pcy*padY + padY+5))){
//                 pieces[i]->isActive = true;
//                 bool castleL = false;
//                 int indexCastleL;
//                 bool castleR = false;
//                 int indexCastleR;
//                 vector<TDT4102::Point> legalMoves = pieces[i]->getLegalMoves(map);

//                 sjekker om du kan castle
//                 if(pieces[i]->getPieceType()==10 and pieces[i]->virginMove){
//                     castleL = castleLeft(i);
//                     castleR = castleRight(i);
//                 }
//                 TDT4102::Point castleCord;
//                 if(castleL){
//                     castleCord.x = pieces[i]->coordinate.x - 2;
//                     castleCord.y = pieces[i]->coordinate.y;
//                     legalMoves.push_back(castleCord);
//                     for(int j = 0; j < pieces.size(); j++){
//                         if(pieces[j]->getPieceType() == 5 and pieces[j]->coordinate.x == pieces[i]->coordinate.x-4 and pieces[j]->coordinate.y == pieces[i]->coordinate.y){
//                             indexCastleL = j;
//                         }
//                     }
//                 }
//                 if(castleR){
//                     castleCord.x = pieces[i]->coordinate.x + 2;
//                     castleCord.y = pieces[i]->coordinate.y;
//                     legalMoves.push_back(castleCord);
//                     for(int j = 0; j < pieces.size(); j++){
//                         if(pieces[j]->getPieceType() == 5 and pieces[j]->coordinate.x == pieces[i]->coordinate.x+3 and pieces[j]->coordinate.y == pieces[i]->coordinate.y){
//                             indexCastleR = j;
//                         }
//                     }
//                 }


                
//                 logikk om brikke er trykket på
//                 while(!is_right_mouse_button_down()){
//                     drawBoard();
//                     drawAroundActivePiece(pcx, pcy); 
//                     drawLegalMoves(legalMoves);
//                     drawPieces();
//                     mouseCord = get_mouse_coordinates();
//                     pieces[i]->coordinate.x = mouseCord.x/padX;
//                     pieces[i]->coordinate.y = mouseCord.y/padY;
//                     next_frame();
//                 }
//                 pieces[i]->isActive = false;


//                 Sjekker om trekket var lovlig
//                 Setter wasMoveLegal til true om det var lovlig
//                 for(const auto& move : legalMoves){
//                     if(pieces[i]->coordinate.x == move.x and pieces[i]->coordinate.y == move.y){
//                         wasMoveLegal = true;
//                         om det var første trekk er ikke de neste et
//                         if(pieces[i]->virginMove){
//                             pieces[i]->virginMove = false;
//                         }
//                         break;
//                     }
//                 }
//                 Resetter pos til piece om ikke
//                 if(!wasMoveLegal){
//                     pieces[i]->coordinate.x = pcx;
//                     pieces[i]->coordinate.y = pcy;
//                 }
//                 else{wasMoveLegal = false;}

//                 om castle
//                 if(castleL and (pieces[indexCastleL]->coordinate.x-pieces[i]->coordinate.x) == -2){
//                     pieces[indexCastleL]->coordinate.x += 3;
//                 }
//                 else if(castleR and (pieces[indexCastleR]->coordinate.x-pieces[i]->coordinate.x == 1)){
//                     pieces[indexCastleR]->coordinate.x -= 2;
//                 }

//                 Fikser om en brikke blir tatt
//                 for(int j = 0; j < pieces.size(); j++){
//                     if((pieces[i]->coordinate.x == pieces[j]->coordinate.x) and (pieces[i]->coordinate.y == pieces[j]->coordinate.y) and (i != j)){
//                         delete pieces[j];
//                         pieces.erase(pieces.begin()+j);
//                         break;
//                     }
//                 }


//                 Fikser om det er promotion
//                 if(pieces[i]->getPieceType() == 1){
//                     if(pieces[i]->side == 1 and pieces[i]->coordinate.y == 0){
//                         promotion(i);
//                     }
//                     else if(pieces[i]->side == -1 and pieces[i]->coordinate.y == 7){
//                         promotion(i);
//                     }
//                 }

//             }
//         }

        
//         next_frame();
//     }
// }




