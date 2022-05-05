#pragma once
#include "GameObject.h"

#define ID_ANI_HAMMER_WORLD_MAP_WALK_RIGHT 109
#define ID_ANI_HAMMER_WORLD_MAP_WALK_LEFT 110
#define HAMMER_WORLD_MAP_WALK_SPEED 0.01f
#define HAMMER_WORLD_MAP_LIMIT_WALK 16
#define HAMMER_WORLD_MAP_STATE_WALK 100
#define HAMMER_WORLD_MAP_STATE_WALK_LEFT 200
class CHammer : public CGameObject
{
	float limitRight;
	float ax;
	float ay;
	float startX;
	int nx;
public:
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = top = right = bottom = 0; }
	virtual void SetState(int state);
	CHammer(float x, float y);
};

