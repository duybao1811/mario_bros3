#pragma once
#include "GameObject.h"

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16
#define MUSHROOM_GRAVITY 0.03f;

#define ID_ANI_RED_MUSHROOM	105
#define ID_ANI_GREEN_MUSHROOM 106

#define MUSHROOM_RUN_SPEED 0.05f;
#define MUSHROOM_SPEED_UP 0.001f;
#define MUSHROOM_SPEED_DOWN 0.001f;

class CMushRoom : public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;
	float startY;

	int model;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);

public:
	CMushRoom(float x, float y, int model);
	virtual void SetState(int state);
};

