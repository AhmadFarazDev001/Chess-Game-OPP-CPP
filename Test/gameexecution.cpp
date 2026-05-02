#include "gameexecution.h"

bool executeGame()
{
	Board board;
	board.setupStartingPosition();
	string currentTurn = "White";
	while (true)
	{
		   #ifdef _WIN32
            system("cls");
           #endif
			
			#ifdef _APPLE_
			system("clear");
			#endif
			cout << "+===============================+\n";
			cout << "|          Chess Board          |\n";
			cout << "+===============================+\n";
			cout << "\n\n";
		cout << "+===============================+\n";
		cout << "|          Turn: " << currentTurn << "          |\n";
		cout << "+===============================+\n";
		cout << "\n";
		board.printBoard();
		cout << "\n\n";
		int startX, startY, endX, endY;
		string startMove,endMove;
		cout << "Enter Piece Position: ";
		cin >> startMove;
		cout << "Enter Destination Position: ";
		cin >> endMove;

		startX = startMove[0] - 'a' + 1;
		startY = 9 - (startMove[1] - '0');
		endX = endMove[0] - 'a' + 1;
		endY = 9 - (endMove[1] - '0');

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
		board.recordPosition(currentTurn);


	}

	return true;
}