#pragma once
#include"Mario.h"
#include "Define.h"
#include "GameTime.h"

class CBackUp
{
public:
	static CBackUp* __instance;
	int health = MARIO_DEFAULT_HEALTH;
	int money = 0;
	DWORD time = 0;
	int score = 0;
	int level = MARIO_LEVEL_SMALL;
	int scene = 0;
	int coin = 0;
	GameTime* gameTime = new GameTime();

	static CBackUp* GetInstance();
	void BackUpMario(CMario* mario);
	void LoadBackUp(CMario* mario);
};
 