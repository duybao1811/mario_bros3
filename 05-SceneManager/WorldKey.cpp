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
		player->SetState(MARIO_WORLD_MAP_STATE_WALK_RIGHT);
		break;
	case DIK_LEFT:
		player->SetState(MARIO_WORLD_MAP_STATE_WALK_LEFT);
		break;
	case DIK_UP:
		player->SetState(MARIO_WORLD_MAP_STATE_WALK_TOP);
		break;
	case DIK_DOWN:
		player->SetState(MARIO_WORLD_MAP_STATE_WALK_BOTTOM);
		break;
	case DIK_S:
	{
		if (player->sceneSwitch != -1) {
			CGame::GetInstance()->InitiateSwitchScene(player->sceneSwitch);
			player->sceneSwitch = -1;
		}
		break;
	}
	}
}
