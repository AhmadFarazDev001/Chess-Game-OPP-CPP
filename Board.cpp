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

	grid[7][0] = new Rook("White");
	grid[7][1] = new Knight("White");
	grid[7][2] = new Bishop("White");
	grid[7][3] = new Queen("White");
	grid[7][4] = new King("White");
	grid[7][5] = new Bishop("White");
	grid[7][6] = new Knight("White");
	grid[7][7] = new Rook("White");
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
			cout << bgDark << " " << ((grid[y - 1][i] != nullptr) ? (grid[y - 1][i]->getsymbol()) : " ") << " " << reset << "|";
		else
			cout << bgBrown << " " << ((grid[y - 1][i] != nullptr) ? (grid[y - 1][i])->getsymbol() : " ") << " " << reset << "|";
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
		if (grid[currY][currX] != nullptr) //-1 beacuse index starts from 0
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
				if (grid[i][j]->getcolor() == kingColor && grid[i][j]->getsymbol() == ((kingColor == "Black") ? "\u265A" : "\u2654"))
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
				if (grid[i][j]->getcolor() != kingColor)
				{
					//Stemp 3: Check the threat
					if (grid[i][j]->isValidMove(j, i, kingX, kingY) == true)
					{
						if (grid[i][j]->getsymbol() == "\u2659" || grid[i][j]->getsymbol() == "\u265F")
						{
							if (j == kingX)
							{
								continue;
							}
						}
							if ((grid[i][j]->getsymbol() == "\u265E") || (grid[i][j]->getsymbol() == "\u2658")) //Check Knight
							{
								return true;
							}
							else if (isPathClear(j, i, kingX, kingY) == true)
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
	if (grid[startY - 1][startX - 1]->getcolor() != currentPlayerColor)
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


	if (grid[startY - 1][startX - 1]->getsymbol() == "\u2659" || grid[startY - 1][startX - 1]->getsymbol() == "\u265F")
	{
		if ((startX == endX) && (grid[endY - 1][endX - 1] != nullptr))
		{
			return false;
		}
		else if ((startX != endX) && (grid[endY - 1][endX - 1] == nullptr))
		{
			return false;
		}
	}

	//Knight can teleport
	//Step 4: Check if the path is clear
	if ((grid[startY - 1][startX - 1]->getsymbol() != "\u265E") && (grid[startY - 1][startX - 1]->getsymbol() != "\u2658"))
	{
		if (isPathClear(startX-1, startY-1, endX-1, endY-1) == false)
		{
			cout << "Error: Path is not clear!" << endl;
			return false;
		}
	}

	//Step 5: Check the destination is empty or not and what is color of destination piece
	if (grid[endY - 1][endX - 1] != nullptr)
	{
		if (grid[endY - 1][endX - 1]->getcolor() == currentPlayerColor)
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

bool Board::isCheckmate(string kingColor)
{
	if (isKingInCheck(kingColor) == false)
	{
		return false;
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (grid[i][j] != nullptr)
			{
				if (grid[i][j]->getcolor() == kingColor)
				{
					//We get friendly piece
					int startX = j, startY = i;
					for (int r = 0; r < 8; r++)
					{
						for (int s = 0; s < 8; s++)
						{
							if (grid[i][j]->isValidMove(startX,startY,s,r)==true)
							{
								if (grid[startY][startX]->getsymbol() == "\u2659" || grid[startY][startX]->getsymbol() == "\u265F")
								{
									if ((startX == s) && (grid[r][s] != nullptr))
									{
										continue;
									}
									else if ((startX != s) && (grid[r][s] == nullptr))
									{
										continue;
									}
								}
									if (grid[r][s] == nullptr || grid[r][s]->getcolor() != kingColor )
									{
										if ((grid[startY][startX]->getsymbol() != "\u265E") && (grid[startY][startX]->getsymbol() != "\u2658"))
										{
											if (isPathClear(startX, startY, s, r) == true)
											{

												//Piece can succesfully move to target Point
												Piece* temp = grid[r][s];
												grid[r][s] = grid[startY][startX];
												grid[startY][startX] = nullptr;
												bool isDanger = isKingInCheck(kingColor);
												//Rewind the whole process
												grid[startY][startX] = grid[r][s];
												grid[r][s] = temp;
												if (!isDanger)
												{
													//Our king is safe
													return false;
												}
											}
										}
										else
										{
											//Piece can succesfully move to target Point
											Piece* temp = grid[r][s];
											grid[r][s] = grid[startY][startX];
											grid[startY][startX] = nullptr;
											bool isDanger = isKingInCheck(kingColor);
											//Rewind the whole process
											grid[startY][startX] = grid[r][s];
											grid[r][s] = temp;
											if (!isDanger)
											{
												//Our king is safe
												return false;
											}
											
										}
									}
								
							}
						}
					}
				}
			}
		}
	}
	//checkmate occurr
	return true;
}
