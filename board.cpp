#include "headerFiles/board.h"

Board::Board(string FEN): FEN{FEN}, en_passant{TDT4102::Point(NULL, NULL)}, turn{1} 
{
    //BoardNewSetup();
    turn = getTurnfromFEN(FEN);
    if(getEPfromFEN(FEN) != "-"){
        en_passant = cordToPoint(getEPfromFEN(FEN));
    }
    createBoardFromFEN(FEN);
    //cout << getEPfromFEN(FEN) << endl;
    //cout << en_passant.x << ", " << en_passant.y << endl;
}

Board::~Board()
{
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            delete the_board[x][y];
            the_board[x][y] = nullptr;
        }
    } 
}


void Board::BoardNewSetup(){

    //nye brikker
    //pawns
    for(int i = 0; i < 8; i++){
        the_board[i][1] = new Pawn(-1); //Black
        the_board[i][6] = new Pawn(1); //White
    }
    //Rooks
    the_board[0][0] = new Rook(-1);
    the_board[7][0] = new Rook(-1);
    the_board[0][7] = new Rook(1);
    the_board[7][7] = new Rook(1);
    //Bishop
    the_board[2][0] = new Bishop(-1);
    the_board[5][0] = new Bishop(-1);
    the_board[2][7] = new Bishop(1);
    the_board[5][7] = new Bishop(1);
    //Horse
    the_board[1][0] = new Horse(-1);
    the_board[6][0] = new Horse(-1);
    the_board[1][7] = new Horse(1);
    the_board[6][7] = new Horse(1);
    //King
    the_board[4][0] = new King(-1);
    the_board[4][7] = new King(1);
    //Queen
    the_board[3][0] = new Queen(-1);
    the_board[3][7] = new Queen(1);

    //Tomme felt
    for(int x = 0; x < 8; x++){
        for(int y = 2; y < 6; y++){
            the_board[x][y] = nullptr;
        }
    }

}

void Board::generateMap(){
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            if(the_board[x][y] != nullptr){
                map[x][y] = the_board[x][y]->getPieceType()*the_board[x][y]->side;
            }
            else{
                map[x][y] = 0;
            }
        }
    }    
}

void Board::Move(TDT4102::Point from, TDT4102::Point to){
    //gjør ikkeno om trekk er utenfor brettet
    if(from.x > 7 or from.x<0 or from.y>7 or from.y<0 or to.x>7 or to.x<0 or to.y>7 or to.y<0)
        return;
    //Sjekker om det er en pawn sitt første trekk, og det skal være lovlig med en passant
    if(abs(the_board[from.x][from.y]->getPieceType()) == 1 and abs(from.y - to.y) == 2){
        if(turn == 1){
            TDT4102::Point ep(from.x,from.y-1);
            en_passant = ep;
        }
        else{
            TDT4102::Point ep(from.x,from.y+1);
            en_passant = ep;
        }
    }
    else{en_passant = TDT4102::Point(NULL, NULL);}

    //Flytter brikka
    the_board[to.x][to.y] = the_board[from.x][from.y];
    the_board[from.x][from.y] = nullptr;

    //Bytter turn
    if(turn == 1){
        turn = -1;
    }
    else{turn = 1;}
}

bool Board::TryToMove(TDT4102::Point from, TDT4102::Point to) const{
    //om trekkene er utenfor brettet
    if(0 > from.x or from.x > 7 or 0 > from.y or from.y > 7 or 0 > to.x or to.x > 7 or 0 > to.y or to.y > 7){return false;}
    Piece* piece = the_board[from.x][from.y];
    //Retrun false om du flytter et tomt felt
    if(piece == nullptr){return false;}
    //Sjekker at det er 'din' tur
    if(piece->side != turn){return false;}
    
    

    //Sjekker om trekket er lovlig;
    vector<TDT4102::Point> legalMoves = piece->getLegalMoves(map, from);
    if(checkEnPassant(from)){
        legalMoves.push_back(GetEnPassant());
    }
        //Sjekker de forskjellige castlene
    if(the_board[from.x][from.y]->getPieceType() == 10){
        if(checkCastleSquares('K')){
            legalMoves.push_back(cordToPoint("g1"));
        }
        if(checkCastleSquares('Q')){
            legalMoves.push_back(cordToPoint("c1"));
        }
        if(checkCastleSquares('k')){
            legalMoves.push_back(cordToPoint("g8"));
        }
        if(checkCastleSquares('q')){
            legalMoves.push_back(cordToPoint("c8"));
        }
    }

    for(TDT4102::Point point : legalMoves){
        if(point.x == to.x and point.y == to.y){
            return true;
        }
    }

    return false;

}

bool Board::TryToMoveFiltered(TDT4102::Point from, TDT4102::Point to) const{
    //om trekkene er utenfor brettet
    if(0 > from.x or from.x > 7 or 0 > from.y or from.y > 7 or 0 > to.x or to.x > 7 or 0 > to.y or to.y > 7){return false;}
    Piece* piece = the_board[from.x][from.y];
    //Retrun false om du flytter et tomt felt
    if(piece == nullptr){return false;}
    //Sjekker at det er 'din' tur
    if(piece->side != turn){return false;}
    

    //Sjekker om trekket er lovlig;
    vector<TDT4102::Point> legalMoves = filterLegalMoves(from);


    for(TDT4102::Point point : legalMoves){
        if(point.x == to.x and point.y == to.y){
            return true;
        }
    }

    return false;

}

TDT4102::Point Board::getKingCord(int side) const{
    TDT4102::Point kingCord;
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            if(the_board[x][y] != nullptr){    
                if(the_board[x][y]->getPieceType() == 10){
                    if(the_board[x][y]->side == side){
                        kingCord.x = x;
                        kingCord.y = y;
                        return kingCord;
                    }
                }
            }
        }
    }
    cout << "fant ikke kongen (Board::getKingCord)" << endl;
    return kingCord;
}

bool Board::isInCheck(int side, TDT4102::Point kingCord) const{

    

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            Piece* tempPiece = the_board[x][y];
            if(tempPiece != nullptr and tempPiece->side != side){
                vector<TDT4102::Point> moves = tempPiece->getLegalMoves(map, TDT4102::Point(x,y));
                for(const auto& cord : moves){
                    if(cord.x == kingCord.x and cord.y == kingCord.y){
                        //cout << "brikken som kan ta kongen da er: " << intToPieceType(tempPiece->getPieceType()) << " som kan flytte til: " << pointToCord(cord) << endl;
                        return true;
                    }
                }
            }
        }
        
    }
    return false;
}

Piece* Board::pieceAt(TDT4102::Point point){
    return the_board[point.x][point.y];
}

void Board::PlacePieceAt(const char piece, TDT4102::Point point){
    switch (piece)
    {
    case 'P':
        the_board[point.x][point.y] = new Pawn(1);
        break;
    case 'N':
        the_board[point.x][point.y] = new Horse(1);
        break;
    case 'B':
        the_board[point.x][point.y] = new Bishop(1);
        break;
    case 'R':
        the_board[point.x][point.y] = new Rook(1);
        break;
    case 'Q':
        the_board[point.x][point.y] = new Queen(1);
        break;
    case 'K':
        the_board[point.x][point.y] = new King(1);
        break;
    case 'p':
        the_board[point.x][point.y] = new Pawn(-1);
        break;
    case 'n':
        the_board[point.x][point.y] = new Horse(-1);
        break;
    case 'b':
        the_board[point.x][point.y] = new Bishop(-1);
        break;
    case 'r':
        the_board[point.x][point.y] = new Rook(-1);
        break;
    case 'q':
        the_board[point.x][point.y] = new Queen(-1);
        break;
    case 'k':
        the_board[point.x][point.y] = new King(-1);
        break;   
    
    default:
        the_board[point.x][point.y] = nullptr;
        //cout << "Placed zeroptr in Board::PlacePieceAt" << endl;
        break;
    } 
    return;
}

TDT4102::Point Board::GetEnPassant() const{
    return en_passant;
}

bool Board::checkCastleSquares(const char castleType) const{
    //Sjekker at rutene er tomme
    bool isSpaceClear = false;
    switch (castleType)
    {
    case 'K':
        if(the_board[cordToPoint("f1").x][cordToPoint("f1").y] == nullptr and the_board[cordToPoint("g1").x][cordToPoint("g1").y] == nullptr){
            isSpaceClear = true;
        } 
        else{
            return false;
        }
        break;
    case 'Q':
        if(the_board[cordToPoint("d1").x][cordToPoint("d1").y] == nullptr and the_board[cordToPoint("c1").x][cordToPoint("c1").y] == nullptr and the_board[cordToPoint("b1").x][cordToPoint("b1").y] == nullptr){
            isSpaceClear = true;
        } 
        else{
            return false;
        }
        break;
    case 'k':
        if(the_board[cordToPoint("f8").x][cordToPoint("f8").y] == nullptr and the_board[cordToPoint("g8").x][cordToPoint("g8").y] == nullptr){
            isSpaceClear = true;
        } 
        else{
            return false;
        }
        break;
    case 'q':
        if(the_board[cordToPoint("d8").x][cordToPoint("d8").y] == nullptr and the_board[cordToPoint("c8").x][cordToPoint("c8").y] == nullptr and the_board[cordToPoint("b8").x][cordToPoint("b8").y] == nullptr){
            isSpaceClear = true;
        } 
        else{
            return false;
        }
        break;
    default:
        cout << "Gitt castleType var ikke KQkq (Board::checkCastleSquares())" << endl;
        return false;
        
        break;
    }

    //Sjekker at castle den veiene er lov
    const string theoreticalCastles = getCastlefromFEN(FEN);
    for(const auto& element : theoreticalCastles){
        if(element == '-'){
            return false;
        }
        if(element == castleType){
            return true;
        }
    }
    cout << "Castle i FEN hadde ikke - eller castletype? (board::checkCastle())" << endl;
    return false;
}

void Board::createBoardFromFEN(const string& FEN){
    int x = 0;
    int y = 0;
    
    const string posFEN = getBoardPosfromFEN(FEN);
    //Lager et helt tomt brett
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            the_board[j][i] = nullptr;
        }
    }
    //plasserer brikker
    for(const auto& element : posFEN){
        switch (element)
        {
        case 'P':
            the_board[x][y] = new Pawn(1);
            //cout << "made pawn in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case 'N':
            the_board[x][y] = new Horse(1);
            //cout << "made horse in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case 'B':
            the_board[x][y] = new Bishop(1);
            //cout << "made bishop in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case 'R':
            the_board[x][y] = new Rook(1);
            //cout << "made rook in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case 'Q':
            the_board[x][y] = new Queen(1);
            //cout << "made queen in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case 'K':
            the_board[x][y] = new King(1);
            //cout << "made king in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case 'p':
            the_board[x][y] = new Pawn(-1);
            //cout << "made black pawn in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case 'n':
            the_board[x][y] = new Horse(-1);
            //cout << "made black horse in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case 'b':
            the_board[x][y] = new Bishop(-1);
            //cout << "made black bishop in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case 'r':
            the_board[x][y] = new Rook(-1);
            //cout << "made black rook in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case 'q':
            the_board[x][y] = new Queen(-1);
            //cout << "made black queen in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case 'k':
            the_board[x][y] = new King(-1);
            //cout << "made black king in " << x << ", " <<  y << endl;
            x += 1;
            break;
        case '1':
            x += 1;
            //cout << "1 empty space" << endl;
            break;
        case '2':
            x += 2;
            //cout << "2 empty space" << endl;
            break;
        case '3':
            x += 3;
            //cout << "3 empty space" << endl;
            break;
        case '4':
            x += 4;
            //cout << "4 empty space" << endl;
            break;
        case '5':
            //cout << "5 empty space" << endl;
            x += 5;
            break;
        case '6':
            x += 6;
            //cout << "6 empty space" << endl;
            break;
        case '7':
            x += 7;
            //cout << "7 empty space" << endl;
            break;
        case '8':
            x += 8;
            //cout << "8 empty space" << endl;
            break;
        case '/':
            x = 0;
            y += 1;
            //cout << "new row, now starting row: " << y << endl;
            break;
        case ' ':
            cout << "Burde ikke vaere space her (Board::createposfromfen)" << endl;
            break;
        default:
            break;
        }
    }
}


void Board::deleteAllPieces(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 0; j++){
            delete the_board[j][i];
            the_board[j][i] = nullptr;
        }
    }
}

vector<TDT4102::Point> Board::filterLegalMoves(TDT4102::Point activeSquare) const{
    //Henter alle pseudolovlige trekk til brikken
    vector<TDT4102::Point> pseudoLegalMoves = the_board[activeSquare.x][activeSquare.y]->getLegalMoves(map, activeSquare);
    int color = the_board[activeSquare.x][activeSquare.y]->side;
    vector<TDT4102::Point>legalMoves;

    Board tempBoard{FEN};
    

    //ser på brikken vi skal sjekke
    Piece* piece = tempBoard.the_board[activeSquare.x][activeSquare.y];
    //om det ikke er en brikke return tom vektor
    if(piece == nullptr){return pseudoLegalMoves;}

    //sjekker om en-passant er relevant, og legger til i legalmoves om det er
    //gjør det her i stedet for legalmoves tilfelle en_passant-capture setter deg ut av sjakk
    //cout << "er leter etter EP? " << checkEnPassant(activeSquare) << endl;
    //cout << FEN << "\t" << "(board::filterlegalmoves)" << endl; 
    //cout << en_passant.x << ", " << en_passant.y << "\t" << "(board::filterlegalmoves)" << endl;
    if(checkEnPassant(activeSquare)){
        //cout << "Er det en EP? " << TryToMove(activeSquare, GetEnPassant()) << endl;
        bool triedToMove = false;
        if(TryToMove(activeSquare, GetEnPassant())){
            triedToMove = true;
        }
        if(triedToMove){
            TDT4102::Point capturedSquare = cordToPoint(getCaptureEPfromFEN(tempBoard.FEN));
            delete tempBoard.the_board[capturedSquare.x][capturedSquare.y];
            tempBoard.the_board[capturedSquare.x][capturedSquare.y] = nullptr;
            tempBoard.Move(activeSquare, GetEnPassant());
            //cout << tempBoard.the_board[2][3]->getPieceType() << endl;
            TDT4102::Point kingCord = tempBoard.getKingCord(color); //her skjer det noe funny
            if(!tempBoard.isInCheck(color, kingCord)){
                legalMoves.push_back(GetEnPassant());
            }
            tempBoard.deleteAllPieces();
            tempBoard.createBoardFromFEN(FEN);
        }
    }

    //Sjekker de forskjellige castlene
    if(the_board[activeSquare.x][activeSquare.y]->getPieceType() == 10 and !isInCheck(color, activeSquare) and color == turn){
        //Går gjennom alle 'mulige' castle
        for(const char& type : getCastlefromFEN(FEN)){
            if(tempBoard.checkCastleSquares(type)){
                TDT4102::Point castleDestination = getCastleDestination(type);
                tempBoard.Move(activeSquare, castleDestination);
                //Hvis du ikke er i sjakk etter trekket
                if(!tempBoard.isInCheck(color, castleDestination)){
                    tempBoard.Move(castleDestination, activeSquare);
                    //Hvis du ikke går gjennom en sjakk
                    if(type == 'K' or type == 'k'){
                        TDT4102::Point middleSquare(castleDestination.x-1, castleDestination.y);
                        tempBoard.Move(activeSquare, middleSquare);
                        //Om tårner står ovenfor failer isincheck under, selvom tårnet ikke har deg i sjakk
                        //isincheck under sier du er i sjakk da, men ikke over når den sjekker å gå 1 vanlig lenger ned i guess
                        if(!tempBoard.isInCheck(color, middleSquare)){
                            legalMoves.push_back(castleDestination);
                        }
                        tempBoard.Move(middleSquare, activeSquare);
                    }
                    else if(type == 'Q' or type == 'q'){
                        TDT4102::Point middleSquare(castleDestination.x+1, castleDestination.y);
                        tempBoard.Move(activeSquare, middleSquare);
                        if(!tempBoard.isInCheck(color, middleSquare)){
                            legalMoves.push_back(castleDestination);
                        }
                        tempBoard.Move(middleSquare, activeSquare);
                    }
                }
                else{
                    tempBoard.Move(castleDestination, activeSquare);
                }
            }
        }
    }
    
    //sjekker om du er i sjakk etter 'vanlige' trekk
    for(int i = 0; i < pseudoLegalMoves.size(); i++){
        tempBoard.generateMap();
        if(TryToMove(activeSquare,pseudoLegalMoves.at(i))){
            //print8x8arr(tempBoard.map);
            tempBoard.Move(activeSquare, pseudoLegalMoves.at(i));
            TDT4102::Point kingCord = tempBoard.getKingCord(color);
            tempBoard.generateMap();
            //cout << "i sjakk etter trekket: " << pointToCord(pseudoLegalMoves.at(i)) << ": " << (tempBoard.isInCheck(color, kingCord)) << endl << endl;
                
            if(!tempBoard.isInCheck(color, kingCord)){
                legalMoves.push_back(pseudoLegalMoves.at(i));
            }
            tempBoard.deleteAllPieces();
            tempBoard.createBoardFromFEN(FEN);
        }
    }

    //tempboard slettes av seg selv når man går ut av funksjonen
    tempBoard.deleteAllPieces();      
    return legalMoves;
}

bool Board::checkEnPassant(TDT4102::Point activeSquare) const{
    //om bonden man ser på er for lang unna uansett return tom
    if(abs(the_board[activeSquare.x][activeSquare.y]->getPieceType())==1 and en_passant.y !=0){
        if((activeSquare.y-en_passant.y)*turn != 1 or abs(activeSquare.x-en_passant.x) != 1){
            return false;
        }

        return true;
    }
    return false;
}

void Board::moveCastle(char type){
    switch (type)
    {
    case 'K':
        Move(cordToPoint("e1"), cordToPoint("g1"));
        turn *= -1;
        Move(cordToPoint("h1"), cordToPoint("f1"));
        break;

    case 'Q':
        Move(cordToPoint("e1"), cordToPoint("c1"));
        turn *= -1;
        Move(cordToPoint("a1"), cordToPoint("d1"));
        break;

    case 'k':
        Move(cordToPoint("e8"), cordToPoint("g8"));
        turn *= -1;
        Move(cordToPoint("h8"), cordToPoint("f8"));
        break;

    case 'q':
        Move(cordToPoint("e8"), cordToPoint("c8"));
        turn *= -1;
        Move(cordToPoint("a8"), cordToPoint("d8"));
        break;
    
    default:
    cout << "Invalid castle type (should be K||Q||k||q)" << endl;
        break;
    }
    return;
}






