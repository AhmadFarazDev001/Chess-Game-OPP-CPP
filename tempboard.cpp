#include "tempboard.h"

// White Pieces
string wKing = "\u2654";   // ♔
string wQueen = "\u2655";  // ♕
string wRook = "\u2656";   // ♖
string wBishop = "\u2657"; // ♗
string wKnight = "\u2658"; // ♘
string wPawn = "\u2659";   // ♙

// Black Pieces
string bKing = "\u265A";   // ♚
string bQueen = "\u265B";  // ♛
string bRook = "\u265C";   // ♜
string bBishop = "\u265D"; // ♝
string bKnight = "\u265E"; // ♞
string bPawn = "\u265F";   // ♟

Board::Board()
{
	////Default Piece Alignment
	pieces[0][0] = new string(bRook);
	pieces[0][1] = new string(bKnight);
	pieces[0][2] = new string(bBishop);
	pieces[0][3] = new string(bQueen);
	pieces[0][4] = new string(bKing);
	pieces[0][5] = new string(bBishop);
	pieces[0][6] = new string(bKnight);
	pieces[0][7] = new string(bRook);

	pieces[1][0] = new string(bPawn);
	pieces[1][1] = new string(bPawn);
	pieces[1][2] = new string(bPawn);
	pieces[1][3] = new string(bPawn);
	pieces[1][4] = new string(bPawn);
	pieces[1][5] = new string(bPawn);
	pieces[1][6] = new string(bPawn);
	pieces[1][7] = new string(bPawn);

	pieces[2][0] = nullptr;
	pieces[2][1] = nullptr;
	pieces[2][2] = nullptr;
	pieces[2][3] = nullptr;
	pieces[2][4] = nullptr;
	pieces[2][5] = nullptr;
	pieces[2][6] = nullptr;
	pieces[2][7] = nullptr;

	pieces[3][0] = nullptr;
	pieces[3][1] = nullptr;
	pieces[3][2] = nullptr;
	pieces[3][3] = nullptr;
	pieces[3][4] = nullptr;
	pieces[3][5] = nullptr;
	pieces[3][6] = nullptr;
	pieces[3][7] = nullptr;

	pieces[4][0] = nullptr;
	pieces[4][1] = nullptr;
	pieces[4][2] = nullptr;
	pieces[4][3] = nullptr;
	pieces[4][4] = nullptr;
	pieces[4][5] = nullptr;
	pieces[4][6] = nullptr;
	pieces[4][7] = nullptr;

	pieces[5][0] = nullptr;
	pieces[5][1] = nullptr;
	pieces[5][2] = nullptr;
	pieces[5][3] = nullptr;
	pieces[5][4] = nullptr;
	pieces[5][5] = nullptr;
	pieces[5][6] = nullptr;
	pieces[5][7] = nullptr;

	pieces[6][0] = new string(wPawn);
	pieces[6][1] = new string(wPawn);
	pieces[6][2] = new string(wPawn);
	pieces[6][3] = new string(wPawn);
	pieces[6][4] = new string(wPawn);
	pieces[6][5] = new string(wPawn);
	pieces[6][6] = new string(wPawn);
	pieces[6][7] = new string(wPawn);

	pieces[7][0] = new string(wRook);
	pieces[7][1] = new string(wKnight);
	pieces[7][2] = new string(wBishop);
	pieces[7][3] = new string(wQueen);
	pieces[7][4] = new string(wKing);
	pieces[7][5] = new string(wBishop);
	pieces[7][6] = new string(wKnight);
	pieces[7][7] = new string(wRook);
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
			cout << bgDark << " " << ((pieces[y - 1][i] != nullptr) ? *(pieces[y - 1][i]) : " ") << " " << reset << "|";
		else
			cout << bgBrown << " " << ((pieces[y - 1][i] != nullptr) ? *(pieces[y - 1][i]) : " ") << " " << reset << "|";
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

void Board::move()
{
#ifdef _WIN32
	system("cls");
#endif
#ifdef _APPLE_
	system("clear");
#endif
	printBoard();
	int startX, startY, endX, endY;
	cout << "Enter Piece Position (X:Y): ";
	cin >> startY >> startX;
	cout << "Enter Position To move (X:Y): ";
	cin >> endY >> endX;

	if (pieces[endY - 1][endX - 1] != nullptr)
	{
		delete pieces[endY - 1][endX - 1];
	}

	pieces[endY - 1][endX - 1] = pieces[startY - 1][startX - 1];
	pieces[startY - 1][startX - 1] = nullptr;
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces[i][j] != nullptr)
			{
				delete pieces[i][j];
			}
		}
	}
}

// Hi i am here
