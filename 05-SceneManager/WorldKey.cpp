#include "WorldKey.h"
#include "WorldPlayer.h"
#include "WorldScene.h"
#include "debug.h"

void CWorldKey::OnKeyDown(int KeyCode)
{
	CWorldPlayer* player = (CWorldPlayer*)((LPWORLDSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_RIGHT:
		if (player->allowRight) {
			player->SetState(MARIO_WORLD_MAP_STATE_WALK_RIGHT);
		}
		break;
	case DIK_LEFT:
		if (player->allowLeft)
		{
			player->SetState(MARIO_WORLD_MAP_STATE_WALK_LEFT);
		}
		break;
	case DIK_UP:
		if (player->allowTop) {
			player->SetState(MARIO_WORLD_MAP_STATE_WALK_TOP);
		}
		break;
	case DIK_DOWN:
		if (player->allowBottom) {
			player->SetState(MARIO_WORLD_MAP_STATE_WALK_BOTTOM);
		}
		break;
	case DIK_S:
	{
		if (player->sceneSwitch != -1 && player->sceneSwitch != 0) {
			CGame::GetInstance()->InitiateSwitchScene(player->sceneSwitch);
			player->sceneSwitch = -1;
		}
		break;
	}
	}
}
