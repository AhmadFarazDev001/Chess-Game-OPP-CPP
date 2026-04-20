#pragma once
#include "library.h"

class Board
{
private:
	string* pieces[8][8];
public:
	Board();
	void printRow(int y);
	void printBoard();
	void move();
	~Board();
};