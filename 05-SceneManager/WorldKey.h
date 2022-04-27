#pragma once

#include "Scene.h"

class CWorldKey : public CSceneKeyHandler
{
	CScene* scene;
public:
	virtual void OnKeyDown(int KeyCode);
	virtual void KeyState(BYTE* states) {};
	virtual void OnKeyUp(int KeyCode) {};
	CWorldKey(LPSCENE s) : CSceneKeyHandler(s) { scene = s; }
};

