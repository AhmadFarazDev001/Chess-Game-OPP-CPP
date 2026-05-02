#ifndef piece_h
#define piece_h


#include"library.h"
//general
class Piece{
protected:
    string color;
    string symbol;
    bool hasmoved;
public:
    Piece(const string _color , const string _symbol);
    virtual ~Piece();
    virtual string getcolor() ;
    virtual string getsymbol() ;
    virtual bool gethasmoved() ;
    virtual void sethasmoved(bool moved) ;
   virtual bool isValidMove(int startX, int startY,int endX, int endY) = 0;
};
//pawn ke lie
class Pawn:public Piece{
public:
    ~Pawn();
    Pawn(const string _color);
    bool isValidMove(int startX, int startY, int endX, int endY) override;
};
//For knight
class Knight:public Piece{
public:
    ~Knight();
    Knight(const string _color);
    bool isValidMove(int startX, int startY, int endX, int endY) override;
};
//queen ke lie
class Queen:public Piece{
public:
    ~Queen();
    Queen(const string _color);
    bool isValidMove(int startX, int startY, int endX, int endY)override;
};
//king ke lie
class King :public Piece{
public:
    ~King();
    King(const string _color);
    bool isValidMove(int startX, int startY, int endX, int endY) override;
};
//bishop
class Bishop :public Piece {
public:
    ~Bishop();
    Bishop(const string _color);
    bool isValidMove(int startX, int startY, int endX, int endY)override;
};
class Rook :public Piece{
public:
    ~Rook();
    Rook(const string _color);
    bool isValidMove(int startX, int startY, int endX, int endY) override;
};
#endif
