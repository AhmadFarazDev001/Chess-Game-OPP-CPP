#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "library.h"

struct RecordGame
{
	string WhiteName;
	string BlackName;
	string result;
	string dateTime;
	void getTime();
	void record();
};



