#include "std_lib_facilities.h"
#include "headerFiles/game.h"

const string startFEN(newBoardFEN);


int main() {

    //Board board{};
    //cout << board.pieceAt(TDT4102::Point(0,3))->getPieceType()*board.pieceAt(TDT4102::Point(0,3))->side << endl;


    //Får feilmelding om man bruker konstruksjonen uten string FEN
    Game game{"rnbqkbnr/pp2pppp/3p4/2pP4/8/8/PPP1PPPP/RNBQKBNR w KQkq c6 0 3"};
  
    game.board.generateMap();

    //cout << game.board.map[0][0] << endl;
    
    game.playGame();



    return 0;
}
