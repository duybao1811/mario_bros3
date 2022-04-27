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
		health = mario->GetHealth();
		score = mario->GetScore();
		level = mario->GetLevel();
		coin = mario->GetCoin();
		gameTime = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetGameTime();
}

void CBackUp::LoadBackUp(CMario* mario)
{
		mario->SetHealth(health);
		mario->SetScore(score);
		mario->SetLevel(level);
		mario->SetCoin(coin);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->SetGameTime(gameTime);
}
