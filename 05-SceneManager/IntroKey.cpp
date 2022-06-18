#include "IntroKey.h"
#include "WorldPlayer.h"
#include "IntroScene.h"
#include "debug.h"
#include "Arrow.h"

void CIntroKey::OnKeyDown(int KeyCode)
{
	CArrow* arrow = (CArrow*)((LPINTROSCENE)CGame::GetInstance()->GetCurrentScene())->GetArrow();

	switch (KeyCode)
	{
	case DIK_UP:
		if (arrow->GetY() != ARROW_POSITION_TOP) {
			arrow->SetPosition(ARROW_DEFAULT_POSITION_X, ARROW_POSITION_TOP);
		}
		break;
	case DIK_DOWN:
		if (arrow->GetY() != ARROW_POSITION_BOTTOM) {
			arrow->SetPosition(ARROW_DEFAULT_POSITION_X, ARROW_POSITION_BOTTOM);
		}
	case DIK_S:
		if (arrow->GetY() == ARROW_POSITION_TOP) {
			CGame::GetInstance()->InitiateSwitchScene(WORLD_MAP_ID);
		}
		break;
	}
}
