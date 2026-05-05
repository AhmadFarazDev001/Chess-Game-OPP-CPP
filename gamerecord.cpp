#include "gamerecord.h"

void RecordGame::getTime()
{
	time_t rawTime = time(0);

	tm* localTime = localtime(&rawTime);

	ostringstream formatedTime;

	formatedTime << put_time(localTime, "%d-%b-%Y %H-%M");

	dateTime = formatedTime.str();
}

void RecordGame::record()
{
	ofstream fout;
	fout.open("gamehistory.txt",std::ios::app);
	if (!fout)
	{
		cout << "File not found!" << endl;
		return;
	}
	fout << WhiteName << " | " << BlackName << " | " << result << " | " << dateTime << endl;
	fout.close();
}