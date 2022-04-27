#pragma once
#include "GameObject.h"

class CWorldPlayer : public CGameObject
{
	int level;
	float ax;
	float ay;
public:
	CWorldPlayer(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x + 32; top = y + 32; right = left + 32; bottom = top +32;
	};
	virtual void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetState(int state);
	void SetLevel(int l) { level = l; };
	void OnCollisionWithDoor(LPCOLLISIONEVENT e);
};

