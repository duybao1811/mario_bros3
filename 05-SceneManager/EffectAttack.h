#pragma once
#include "GameObject.h"
#include "define.h"

#define ID_ANI_EFFECT_ATTACK 509
#define EFFECT_ATTACK_TIME_OUT 400
#define EFFECT_ATTACK_STATE_SHOW 100

class CEffectAttack : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG effect_start = -1;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = top = right = bottom = 0; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CEffectAttack(float x, float y);
	virtual void SetState(int state);
};

