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
		left = x - 16/2; top = y - 16/2; right = left + 16; bottom = top +16;
	};
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithDoor(LPCOLLISIONEVENT e);
	void OnCollisionWithBlockObj(LPCOLLISIONEVENT e);
	void SetState(int state);
	void SetLevel(int l) { level = l; };
	int sceneSwitch = -1;
	BOOLEAN isReadySwitchScene = false;
};

