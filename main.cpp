#include "std_lib_facilities.h"
#include "headerFiles/game.h"

const string startFEN(newBoardFEN);


int main() {

    //Board board{};
    //cout << board.pieceAt(TDT4102::Point(0,3))->getPieceType()*board.pieceAt(TDT4102::Point(0,3))->side << endl;



    Game game{};

    game.board.generateMap();

    //cout << game.board.map[0][0] << endl;
    
    game.playGame();



    return 0;
}
