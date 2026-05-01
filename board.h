#pragma once
#include "library.h"
#include "Piece.h"

using namespace std;

class Board {
private:
    //COMPOSITION: The Board "has" Pieces.
    Piece* grid[8][8];
    int fiftyMoveCounter;
    map<string , int>positionhistory;
    string positiongeneratekey(string currentplayercolor);
public:
    Board();
    ~Board();

    void setupStartingPosition();
    void printRow(int y);
    void printBoard();
    // Helper Engine Functions
    bool isPathClear(int startX, int startY, int endX, int endY);
    // Turn Management
    // This function will call the Piece's isValidMove, check isPathClear,
    // handle capturing, and finally swap the pointers.
    bool executeMove(int startX, int startY, int endX, int endY, string currentPlayerColor);

    // Game State Scanners
    void recordPosition(string currentPlayerColor);
    bool isThreefoldRepetition(string currentPlayerColor);
    bool isKingInCheck(string kingColor);
    bool hasLegalMoves(string kingColor);
    bool isCheckmate(string kingColor);
    bool isStalemate(string kingColor);
    bool isDraw(string currentplayercolor);
    bool islesspeice();
    bool isThreefoldRepetition();
};
