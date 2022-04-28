#pragma once
#include "GameObject.h"
#define MARIO_WORLD_MAP_BBOX_WIDTH 8
#define MARIO_WORLD_MAP_BBOX_HEIGHT 8

class CWorldPlayer : public CGameObject
{
	int level;
	float ax;
	float ay;
public:
	int allowLeft = 1, allowRight = 1, allowBottom = 0, allowTop = 0;
	CWorldPlayer(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x - MARIO_WORLD_MAP_BBOX_WIDTH/2; top = y - MARIO_WORLD_MAP_BBOX_WIDTH/2; right = left + MARIO_WORLD_MAP_BBOX_HEIGHT; bottom = top + MARIO_WORLD_MAP_BBOX_HEIGHT;
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

