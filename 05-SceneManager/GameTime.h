#pragma once
#include "GameObject.h"
#define ONE_SECOND 1000
class GameTime
{
	DWORD temp;
	int time;
public:
	GameTime();
	void Update(DWORD dt);
	void SetTime(int t);
	int GetTime();
};

