#include "Backup.h"
#include "PlayScene.h"

CBackUp* CBackUp::__instance = NULL;
CBackUp* CBackUp::GetInstance()
{
	if (__instance == NULL) __instance = new CBackUp();
	return __instance;
}

void CBackUp::BackUpMario(CMario* mario)
{
	if (mario != NULL)
	{
		health = mario->health;
		score = mario->score;
		level = mario->level;

		//scene = CGame::GetInstance()->GetCurrentScene()->GetId();
		//if (scene == 2 || scene == 5)
		//	scene--;
		//cards = mario->cards;
	}

}

void CBackUp::LoadBackUp(CMario* mario)
{
	if (mario != NULL)
	{
		mario->health = health;
		mario->score = score;
		mario->level = level;
	}

}
