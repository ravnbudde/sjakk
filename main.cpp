#include "std_lib_facilities.h"
#include "headerFiles/game.h"

const string startFEN(newBoardFEN);


int main() {

    //Board board{};
    //cout << board.pieceAt(TDT4102::Point(0,3))->getPieceType()*board.pieceAt(TDT4102::Point(0,3))->side << endl;


    //Får feilmelding om man bruker konstruksjonen uten string FEN
    Game game{"8/3k4/8/1Pp5/1K6/8/8/8 w - c6 0 2"};
    //Game game{};
    game.board.generateMap();

    //cout << game.board.map[0][0] << endl;
    
    game.playGame();



    return 0;
}
