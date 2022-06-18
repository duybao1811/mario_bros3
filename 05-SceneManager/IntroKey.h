#pragma once

#include "Scene.h"

#define ARROW_POSITION_TOP 146

#define ARROW_POSITION_BOTTOM 162

#define ARROW_DEFAULT_POSITION_X 70
class CIntroKey : public CSceneKeyHandler
{
	CScene* scene;
public:
	virtual void OnKeyDown(int KeyCode);
	virtual void KeyState(BYTE* states) {};
	virtual void OnKeyUp(int KeyCode) {};
	CIntroKey(LPSCENE s) : CSceneKeyHandler(s) { scene = s; }
};

