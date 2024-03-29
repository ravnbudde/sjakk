#include "std_lib_facilities.h"
#include "headerFiles/game.h"

const string startFEN(newBoardFEN);


int main() {

    //Game game{"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1"}; //castle setup

    //Game game{"4k3/2p5/8/1P6/8/1K6/8/8 b - - 0 1"}; //EnPassant setup

    //Game game{"r3k3/1P6/8/8/8/8/3p4/K7 w q - 0 1"}; //Promotion setup

    //Game game{"rnbqkbnr/p7/8/8/8/8/P7/RNBQKBNR w KQkq - 0 1"}; //movecount setup

    //Game game{"rr2k3/8/8/8/8/8/8/4K3 w - - 0 1"}; //Mate setup

    Game game{};

    game.board.generateMap();

    
    game.playGame2Player();



    return 0;
}
