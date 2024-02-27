#include "headerFiles/window.h"
enum PieceName{
    Pawn = 1, 
    Horse = 2, 
    Bishop = 4, 
    Rook = 5, 
    Queen = 9, 
    King = 10
};

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
    for(int i = 0; i < 8; i++){
        char letter = static_cast<char>(96+i);
        if(i%2 == 0){
            draw_text({-2*padX/100, i*padY+padY/100}, to_string(8-i), TDT4102::Color(175,144,117), 20, TDT4102::Font::courier_bold);
            draw_text({i*padX-2*padX/10, 7*padY+75*padY/100}, to_string(letter), TDT4102::Color(175,144,117), 20, TDT4102::Font::courier_bold);
        }
        else{
            draw_text({-2*padX/100, i*padY+padY/100}, to_string(8-i), TDT4102::Color(253, 238, 211), 20, TDT4102::Font::courier_bold);
            draw_text({i*padX-2*padX/10, 7*padY+75*padY/100}, to_string(letter), TDT4102::Color(253, 238, 211), 20, TDT4102::Font::courier_bold);
        }
    }
    //Gudene vet hvorfor h ikke kommer med i loopen over
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
    draw_text({8*padX, 1*padY}, whiteTime, TDT4102::Color::black, winW*75/1000);
    //Tegner sort tid
    draw_rectangle({8*padX, 0*padY}, 2*padX, 1*padY, TDT4102::Color::black);
    draw_text({8*padX, 0*padY}, blackTime, TDT4102::Color::white, winW*75/1000);
}

void SjakkWindow::drawUndo(){
    draw_rectangle({8*padX, 2*padY}, padX, padY, TDT4102::Color::gray, TDT4102::Color::black);
    draw_triangle({int(8*padX+padX/10), int(2*padY+5*padY/10)}, {int(8*padX+3*padX/10), int(2*padY+7*padY/10)}, {int(8*padX+3*padX/10),int(2*padY+3*padY/10)}, TDT4102::Color::black);
    draw_rectangle({int(8*padX+3*padX/10), int(2*padY+4*padY/10)}, 6*padX/10, 2*padY/10, TDT4102::Color::black);
}

void SjakkWindow::drawForward(){
    draw_rectangle({9*padX, 2*padY}, padX, padY, TDT4102::Color::gray, TDT4102::Color::black);
    draw_triangle({int(10*padX-1*padX/10), int(2*padY+5*padY/10)}, {int(10*padX-3*padX/10), int(2*padY+7*padY/10)}, {int(10*padX-3*padX/10),int(2*padY+3*padY/10)}, TDT4102::Color::black);
    draw_rectangle({int(10*padX-9*padX/10), int(2*padY+4*padY/10)}, 6*padX/10, 2*padY/10, TDT4102::Color::black);
}


void SjakkWindow::drawLastMove(const string from, const string to){
    TDT4102::Color darkColor(228, 167, 31);
    TDT4102::Color lightColor(255, 192, 66);
    TDT4102::Point fromPoint = cordToPoint(from);
    TDT4102::Point toPoint = cordToPoint(to);
    if((fromPoint.x+fromPoint.y)%2 == 0){
        draw_rectangle({fromPoint.x*padX, fromPoint.y*padY}, padX, padY, lightColor);
    }
    else{
        draw_rectangle({fromPoint.x*padX, fromPoint.y*padY}, padX, padY, darkColor);
    }

    if((toPoint.x+toPoint.y)%2 == 0){
        draw_rectangle({toPoint.x*padX, toPoint.y*padY}, padX, padY, lightColor);
    }
    else{
        draw_rectangle({toPoint.x*padX, toPoint.y*padY}, padX, padY, darkColor);
    }
}