#include "Board.h"

Board::Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			grid[i][j] = nullptr;
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if(grid[i][j] != nullptr)
			delete grid[i][j];
		}
	}
}

void Board::setupStartingPosition()
{
	//Default Piece Alignment
	grid[0][0] = new Rook("Black");
	grid[0][1] = new Knight("Black");
	grid[0][2] = new Bishop("Black");
	grid[0][3] = new Queen("Black");
	grid[0][4] = new King("Black");
	grid[0][5] = new Bishop("Black");
	grid[0][6] = new Knight("Black");
	grid[0][7] = new Rook("Black");

	grid[1][0] = new Pawn("Black");
	grid[1][1] = new Pawn("Black");
	grid[1][2] = new Pawn("Black");
	grid[1][3] = new Pawn("Black");
	grid[1][4] = new Pawn("Black");
	grid[1][5] = new Pawn("Black");
	grid[1][6] = new Pawn("Black");
	grid[1][7] = new Pawn("Black");

	grid[6][0] = new Pawn("White");
	grid[6][1] = new Pawn("White");
	grid[6][2] = new Pawn("White");
	grid[6][3] = new Pawn("White");
	grid[6][4] = new Pawn("White");
	grid[6][5] = new Pawn("White");
	grid[6][6] = new Pawn("White");
	grid[6][7] = new Pawn("White");

	grid[7][0] = new Rook("Whiht");
	grid[7][1] = new Knight("Whiht");
	grid[7][2] = new Bishop("Whiht");
	grid[7][3] = new Queen("Whiht");
	grid[7][4] = new King("Whiht");
	grid[7][5] = new Bishop("Whiht");
	grid[7][6] = new Knight("Whiht");
	grid[7][7] = new Rook("Whiht");
}

void Board::printRow(int y)
{
	string bgBrown = "\033[48;2;139;69;19m";
	string bgDark = "\033[48;2;100;50;10m";
	string reset = "\033[0m";
	cout << "  +---+---+---+---+---+---+---+---+\n";
	cout << y << " |";
	for (int i = 0; i < 8; i++)
	{

		if ((y + i) % 2 == 0)
			cout << bgDark << " " << ((grid[y - 1][i] != nullptr) ? (grid[y - 1][i]->getSymbol()) : " ") << " " << reset << "|";
		else
			cout << bgBrown << " " << ((grid[y - 1][i] != nullptr) ? (grid[y - 1][i])->getSymbol() : " ") << " " << reset << "|";
	}
	cout << "\n";
}

void Board::printBoard()
{
	cout << "+===============================+\n";
	cout << "|          Chess Board          |\n";
	cout << "+===============================+\n";
	cout << "\n\n\n";

	cout << "   1   2   3   4   5   6   7   8\n";
	for (int i = 1; i <= 8; i++)
	{
		printRow(i);
	}
	cout << "  +---+---+---+---+---+---+---+---+\n";
}

bool Board::isPathClear(int startX, int startY, int endX, int endY)
{
	int moveX, moveY;

	//Calculating X steps
	if (startX == endX)
	{
		moveX = 0; //Piece move vertically
	}
	else if (startX < endX)
	{
		moveX = 1; //Piece moves right
	}
	else if (startX > endX)
	{
		moveX = -1; //piece moves left
	}

	//Calculating Y steps
	if (startY == endY)
	{
		moveY = 0; //Piece move Horizontally
	}
	else if (startY < endY)
	{
		moveY = 1; //Piece moves down
	}
	else if (startY > endY)
	{
		moveY = -1; //Piece moves Up
	}


	//If startX > or < endX and startY > or < endY it means Piece moves diagnally

	int currX=startX + moveX, currY=startY + moveY;

	while (currX != endX || currY != endY)
	{
		if (grid[currY - 1][currX - 1] != nullptr) //-1 beacuse index starts from 0
		{
			return false;
		}
		currX += moveX;
		currY += moveY;
	}

	return true;

}

bool Board::isKingInCheck(string kingColor)
{
	int kingX = 0, kingY = 0;
	//Step 1: Get King Corrdinates
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] != nullptr)
			{
				if (grid[i][j]->getColor() == kingColor && grid[i][j]->getSymbol() == ((kingColor == "Black") ? "\u265A" : "\u2654"))
				{
					kingX = j; kingY = i;
				}
			}
		}
	}

	//Step 2: Look for enime piece
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] != nullptr)
			{
				if (grid[i][j]->getColor() != kingColor)
				{
					//Stemp 3: Check the threat
					if (grid[i][j]->isValidMove(j, i, kingX, kingY) == true)
					{
						if ((grid[i][j]->getSymbol() == "\u265E") || (grid[i][j]->getSymbol() == "\u2658")) //Check Knight
						{
							return true;
						}
						else if(isPathClear(j, i, kingX, kingY) == true)
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

bool Board::executeMove(int startX, int startY, int endX, int endY, string currentPlayerColor)
{
	//Step 1: Check if square is empty or not
	if (grid[startY - 1][startX - 1] == nullptr)
	{
		cout << "Error:Square is empty!" << endl;
		return false;
	}

	//Step 2: Check square ownership
	if (grid[startY - 1][startX - 1]->getColor() != currentPlayerColor)
	{
		cout << "Error: Enemy Piece!" << endl;
		return false;
	}

	//Step 3: Checks if a piece move correct
	if (grid[startY - 1][startX - 1]->isValidMove(startX, startY, endX, endY) == false)
	{
		cout << "Error: Invalid Move!" << endl;
		return false;
	}

	//Knight can teleport
	//Step 4: Check if the path is clear
	if ((grid[startY - 1][startX - 1]->getSymbol() != "\u265E") && (grid[startY - 1][startX - 1]->getSymbol() != "\u2658"))
	{
		if (isPathClear(startX, startY, endX, endY) == false)
		{
			cout << "Error: Path is not clear!" << endl;
			return false;
		}
	}

	//Step 5: Check the destination is empty or not and what is color of destination piece
	if (grid[endY - 1][endX - 1] != nullptr)
	{
		if (grid[endY - 1][endX - 1]->getColor() == currentPlayerColor)
		{
			cout << "Error: Player Piece!" << endl;
			return false;
		}
	}

	//Step 6: Execute the move and check for CHECKS
	Piece* tempPiece = grid[endY - 1][endX - 1];
	grid[endY - 1][endX - 1] = grid[startY - 1][startX - 1];
	grid[startY - 1][startX - 1] = nullptr;
	if (isKingInCheck(currentPlayerColor) == true)
	{
		grid[startY - 1][startX - 1] = grid[endY - 1][endX - 1];
		grid[endY - 1][endX - 1] = tempPiece;
		cout << "Error: King is in CHECK" << endl;
		return false;
	}
	else
	{
		delete tempPiece;
		return true;
	}

	return true;

}

