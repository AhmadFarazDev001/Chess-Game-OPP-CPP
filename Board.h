#pragma once
#include "library.h"

using namespace std;

class Board {
private:
    //COMPOSITION: The Board "has" Pieces. 
    Piece* grid[8][8];

    // Helper Engine Functions (Encapsulated so the user can't mess with them)
    bool isPathClear(int startX, int startY, int endX, int endY);

public:
    Board();
    ~Board();

    void setupStartingPosition();
    void printBoard();

    // Turn Management
    // This function will call the Piece's isValidMove, check isPathClear, 
    // handle capturing, and finally swap the pointers.
    bool executeMove(int startX, int startY, int endX, int endY, string currentPlayerColor);

    // Game State Scanners
    bool isKingInCheck(string kingColor);
    bool isCheckmate(string kingColor);
};