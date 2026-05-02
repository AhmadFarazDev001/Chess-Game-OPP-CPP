//there is function abs is used as in mathemetics abs used in th programming it gives positive only chess only matters distance
#include"Piece.h"
//piece class
Piece::Piece(const string _color , const string _symbol):color(_color) , symbol(_symbol)
{
    hasmoved = false;
};
string Piece::getcolor(){
    return color;
}
string Piece::getsymbol(){
    return symbol;
}
void Piece::sethasmoved(bool moved){
    hasmoved = moved;
}
bool Piece::gethasmoved()
{
    return hasmoved;
}
Piece::~Piece() {};

//Pawn class

Pawn::Pawn(const string _color) :Piece(_color, "") {
    if (_color == "White") {
        symbol = "\u2659";
    }
    else if (_color == "Black") {
        symbol = "\u265F";
    }
};
bool Pawn::isValidMove(int startX, int startY, int endX, int endY){
    int dx = endX - startX;
    int dy = endY - startY;
    //Y upward
    if(color == "Black"){
        // step forward
        if(dx == 0 && dy ==1){
            return true;
        }
        if(dx == 0 && dy == 2 && hasmoved == false){
            return true;
        }
        if((dx== 1 || dx == -1)&& dy == 1){
            return true;
        }
    }
    // Y downward
    if(color == "White"){
        // step forward
        if(dx == 0 && dy ==-1){
            return true;
        }
        if(dx == 0 && dy ==-2 && hasmoved == false){
            return true;
        }
        if((dx== 1 || dx ==-1)&& dy == -1){
            return true;
        }
    }
    return false;
}
Pawn::~Pawn() {};

//Kinght Class
bool Knight::isValidMove(int startX, int startY, int endX, int endY){
    int dx = endX - startX;
    int dy = endY - startY;
    if (
        (dx == 2 && dy == 1)  ||(dx == 2 && dy == -1) ||(dx == -2 && dy == 1) ||(dx == -2 && dy == -1) || (dx == 1 && dy == 2)  ||(dx == 1 && dy == -2) || (dx == -1 && dy == 2) ||(dx == -1 && dy == -2)){
            return true;
        }
    return false;
}

Knight::Knight(const string _color) :Piece(_color, "") {
    if (_color == "White") {
        symbol = "\u2658";
    }
    else if (_color == "Black") {
        symbol = "\u265E";
    }

};
Knight::~Knight() {};
//Bishop Class
bool Bishop::isValidMove(int startX, int startY, int endX, int endY){
    int dx = endX - startX;
    int dy = endY - startY;
    //only diagnoll
    if(abs(dx) == abs(dy)){
        return true;
    }
    //so -dx == -dy and dx == dy all are covered dx == -dy and -dx == dy
    
    return false;
}
Bishop::Bishop(const string _color) :Piece(_color, "") {
    if (_color == "White") {
        symbol = "\u2657";
    }
    else if (_color == "Black") {
        symbol = "\u265D";
    }
};
Bishop::~Bishop() {};


//King Class
bool King::isValidMove(int startX, int startY, int endX, int endY){
    int dx = endX - startX;
    int dy = endY - startY;
    //only diagnoll
    if(abs(dx)<=1 && abs(dy) <= 1){
        return true;
    }
    //king can move only one box diagnol horizontal and vertical
    
    return false;
}
King::King(const string _color) :Piece(_color, "") {
    if (_color == "White") {
        symbol = "\u2654";
    }
    else if (_color == "Black") {
        symbol = "\u265A";
    }
};
King::~King() {};
bool Queen::isValidMove(int startX, int startY, int endX, int endY){
    int dx = endX - startX;
    int dy = endY - startY;
    //only diagnoll
    if((dx == 0 || dy == 0)||(abs(dx) == abs(dy))){
        return true;
    }
    //queen only moves in diagnoll
    
    return false;
}

//Queen Class
Queen::Queen(const string _color) : Piece(_color, "") {
    if (_color == "White") {
        symbol = "\u2655";
    }
    else if (_color == "Black") {
        symbol = "\u265B";
    }

};
Queen::~Queen() {};
bool Rook::isValidMove(int startX, int startY, int endX, int endY){
    int dx = endX - startX;
    int dy = endY - startY;
    //only diagnoll
    if(dx == 0 || dy == 0){
        return true;
    }
//rook only moves in straight line
    return false;
}

//Rook Class
Rook::Rook(const string _color) :Piece(_color, "") {
    if (_color == "White") {
        symbol = "\u2656";
    }
    else if (_color == "Black") {
        symbol = "\u265C";
    }
};
Rook::~Rook() {};

