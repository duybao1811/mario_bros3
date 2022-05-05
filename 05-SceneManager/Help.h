#pragma once
#include "GameObject.h"

#define ID_ANI_HELP_WORLD_MAP 111

class CHelp : public CGameObject
{
public:
	CHelp(float x, float y) : CGameObject(x, y) {}
	virtual void Render();
	void Update(DWORD dt) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = top = right = bottom = 0; }
};

