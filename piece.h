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
    Pawn(const string _color):Piece(_color , "" ){
        string symbol;
        if(_color == "White"){
            symbol    ="\u2659";
        }else if(_color  == "Black"){
            symbol = "\u265F";
        }
        
    };
    bool isValidMove(int startX, int startY, int endX, int endY) override;
};
//knight ke lie
class Knight:public Piece{
public:
    ~Knight();
    Knight(const string _color):Piece(_color , "" ){
        string symbol;
        if(_color == "White"){
            symbol    ="\u2654";
        }else if(_color  == "Black"){
            symbol = "\u265E";
        }
        
    };
    bool isValidMove(int startX, int startY, int endX, int endY) override;
};
//queen ke lie
class Queen:public Piece{
public:
    ~Queen();
    Queen(const string _color): Piece(_color , "" ){
        string symbol;
        if(_color == "White"){
            symbol    = "\u2658";
        }else if(_color  == "Black"){
            symbol = "\u265B";
        }
        
    };
    bool isValidMove(int startX, int startY, int endX, int endY)override;
};
//king ke lie
class King :public Piece{
public:
    ~King();
    King(const string _color):Piece(_color , "" ){
        string symbol;
        if(_color == "White"){
            symbol    = "\u2654";
        }else if(_color  == "Black"){
            symbol = "\u265A";
        }
    };
    bool isValidMove(int startX, int startY, int endX, int endY) override;
};
//bishop
class Bishop :public Piece {
public:
    ~Bishop();
    Bishop(const string _color):Piece(_color , "" ){
        string symbol;
        if(_color == "White"){
            symbol    = "\u2657";
        }else if(_color  == "Black"){
            symbol = "\u265D";
        }
    };
    bool isValidMove(int startX, int startY, int endX, int endY)override;
};
class Rook :public Piece{
public:
    ~Rook();
    Rook(const string _color):Piece(_color , "" ){
        string symbol;
        if(_color == "White"){
            symbol    = "\u2656";
        }else if(_color  == "Black"){
            symbol = "\u265C";
        }
    };
    bool isValidMove(int startX, int startY, int endX, int endY) override;
};
#endif
