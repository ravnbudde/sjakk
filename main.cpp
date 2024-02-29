#include "std_lib_facilities.h"
#include "headerFiles/game.h"

const string startFEN(newBoardFEN);


int main() {

    //Board board{};
    //cout << board.pieceAt(TDT4102::Point(0,3))->getPieceType()*board.pieceAt(TDT4102::Point(0,3))->side << endl;

    // Board test{};
    // cout << startFEN << endl; 
    // test.FEN = startFEN;
    // cout << test.FEN << endl;


    // //skjønner ikke?? den funksjonen lager en litt random board?
    // //lager samme før første trekket i board::filterlegalmoves også
    // //men etter første trekket funker den som det skal? hæ
    // test.createBoardFromFEN(test.FEN);

    // test.generateMap();
    // print8x8arr(test.map);


    Game game{};

    game.board.generateMap();

    //cout << game.board.map[0][0] << endl;
    
    game.playGame();



    return 0;
}
