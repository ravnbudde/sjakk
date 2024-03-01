#include "std_lib_facilities.h"
#include "headerFiles/game.h"

const string startFEN(newBoardFEN);


int main() {

    //Board board{};
    //cout << board.pieceAt(TDT4102::Point(0,3))->getPieceType()*board.pieceAt(TDT4102::Point(0,3))->side << endl;


    //Får feilmelding om man bruker konstruksjonen uten string FEN
    Game game{"2r5/3pk3/8/2P5/8/2K5/8/8 w - - 5 4"};
  
    game.board.generateMap();

    //cout << game.board.map[0][0] << endl;
    
    game.playGame();



    return 0;
}
