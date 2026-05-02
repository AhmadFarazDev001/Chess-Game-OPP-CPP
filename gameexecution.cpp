#include "gameexecution.h"

void pauseWithError(string message) {
	cout << "\033[1;31m" << message << "\033[0m" << endl; 
	cout << "Press Enter to continue...";
	cin.ignore(1000, '\n'); 
	cin.get();           
}

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
			
			#ifdef __APPLE__
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
		if (startMove.length() != 2 || startMove[0] < 'a' || startMove[0] > 'h' || startMove[1] < '1' || startMove[1] > '8') {
			pauseWithError("Invalid input format! Use coordinates like 'a2'.");
			continue;
		}
		cout << "Enter Destination Position: ";
		cin >> endMove;
		if (endMove.length() != 2 || endMove[0] < 'a' || endMove[0] > 'h' || endMove[1] < '1' || endMove[1] > '8') {
			pauseWithError("Invalid destination format! Use coordinates like 'a4'.");
			continue;
		}
		startX = startMove[0] - 'a' + 1;
		startY = 9 - (startMove[1] - '0');
		endX = endMove[0] - 'a' + 1;
		endY = 9 - (endMove[1] - '0');

		if (board.executeMove(startX, startY, endX, endY,currentTurn) == false)
		{
			pauseWithError("Move failed! Please review the error above.");
			continue;
		}

		string opponent = (currentTurn == "White") ? "Black" : "White";

		if (board.isCheckmate(opponent))
		{
			#ifdef _WIN32
			system("cls");
			#else
			system("clear");
			#endif
			board.printBoard();
			cout << "\n\033[1;32mCHECKMATE! Winner: " << currentTurn << "\033[0m" << endl;
			break;
		}

		if (board.isDraw(opponent))
		{
			cout << "Game ended in a Draw!" << endl;
			break;
		}
		currentTurn = opponent;
		board.recordPosition(currentTurn);
		cin.ignore(1000, '\n');
	}

	return true;
}