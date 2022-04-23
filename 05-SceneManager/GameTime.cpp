#include "GameTime.h"
GameTime::GameTime()
{
	this->temp = 0;
	this->time = 0;
}

void GameTime::Update(DWORD dt)
{
	if (temp + dt <= ONE_SECOND) {
		temp += dt;
	}
	else {
		temp = 0;
		time++;
	}
}

void GameTime::SetTime(int t)
{
	time = t;
}

int GameTime::GetTime()
{
	return time;
}