#pragma once
#include "GameObject.h"
#include "define.h"

#define SCORE_EFFECT_MAX_HEIGHT 50
#define SCORE_EFFECT_SPEED 0.1f



#define SCORE_EFFECT_100 1
#define SCORE_EFFECT_200 2
#define SCORE_EFFECT_400 3
#define SCORE_EFFECT_800 4
#define SCORE_EFFECT_1000 5
#define SCORE_EFFECT_2000 6
#define SCORE_EFFECT_4000 7
#define SCORE_EFFECT_8000 8
#define EFFECT_1_UP 9

class CEffectScore : public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;

	BOOLEAN isFinish = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = top = right = bottom = 0; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt);
	virtual void Render();

public:
	CEffectScore(float x, float y, int model);
	void SetScoreMario();
};

