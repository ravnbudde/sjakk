#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#pragma once





class Piece {
    public:
    Piece(int x, int y, int side);
    virtual ~Piece();
    virtual string getBasePath() const;


    TDT4102::Point coordinate; //Lagre koordinatene til hver enkel piece
    int side; //0 om sort, 1 om hvit
    TDT4102::Image sprite;
    

};

class Pawn : public Piece {
    public:
    Pawn(int x, int y, int side);
    string basePath; //path til brikken sin png fil, legger til hvit eller sort basert på int side

    string getBasePath() const override;
};

class Rook : public Piece {
    public:
    Rook(int x, int y, int side);
    string basePath;

    string getBasePath() const override;
};

class Bishop : public Piece {
    public:
    Bishop(int x, int y, int side);
    string basePath;

    string getBasePath() const override;
};

class Horse : public Piece {
    public:
    Horse(int x, int y, int side);
    string basePath;

    string getBasePath() const override;
};

class Queen : public Piece {
    public:
    Queen(int x, int y, int side);
    string basePath;

    string getBasePath() const override;
};

class King : public Piece {
    public:
    King(int x, int y, int side);
    string basePath;

    string getBasePath() const override;
};

