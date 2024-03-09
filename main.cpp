#include "std_lib_facilities.h"
#include "headerFiles/game.h"

const string startFEN(newBoardFEN);


int main() {

    //Game game{"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1"}; //castle setup

    //Game game{"4k3/2p5/8/1P6/8/1K6/8/8 b - - 0 1"}; //EnPassant setup

    Game game{"r3k3/1P6/8/8/8/8/8/K7 w q - 0 1"}; //Promotion setup

    //Game game{};

    game.board.generateMap();

    //cout << game.board.map[0][0] << endl;
    
    game.playGame2Player();



    return 0;
}
