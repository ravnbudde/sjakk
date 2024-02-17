#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "headerFiles/window.h"



int main() {






    SjakkWindow win{};
    win.piecesNewSetup();


    win.movepiece();

    for(const auto& piece : win.pieces){
        delete piece;
    }
    win.pieces.clear();



    return 0;
}
