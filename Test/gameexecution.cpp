#include "gameexecution.h"

bool executeGame()
{
	Board board;
	board.setupStartingPosition();
	string currentTurn = "White";
	cout << "+===============================+\n";
	cout << "|          Chess Board          |\n";
	cout << "+===============================+\n";
	cout << "\n\n\n";
	while (true)
	{
		cout << "+===============================+\n";
		cout << "|          Turn: " << currentTurn << "          |\n";
		cout << "+===============================+\n";
		cout << "\n\n";
		board.printBoard();
		cout << "\n\n";
		int startX, startY, endX, endY;
		string startMove,endMove;
		cout << "Enter Piece Position: ";
		cin >> startMove;
		cout << "Enter Destination Position: ";
		cin >> endMove;

		startX = 'e' - startMove[0] + 1;
		startY = startMove[1];
		endX = 'e' - endMove[0] + 1;
		endY = endMove[1];

		if (board.executeMove(startX, startY, endX, endY,currentTurn) == false)
		{
			cout << "Wrong Move! Try Again.\n";
			continue;
		}

		string opponent = (currentTurn == "White") ? "Black" : "White";

		if (board.isCheckmate(opponent))
		{
			cout << "Winner: " << currentTurn << endl;
			break;
		}

		if (board.isDraw(opponent))
		{
			cout << "Draw!" << endl;
			break;
		}

		currentTurn = opponent;
	
           #ifdef _WIN32
            system("cls");
           #endif
			
			#ifdef _APPLE_
			system("clear");
			#endif



	}

	return true;
}