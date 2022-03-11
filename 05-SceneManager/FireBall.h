#pragma once

#include "GameObject.h"

#define FIRE_BALL_GRAVITY 0.0006f
#define FIRE_BALL_SPEED 0.15f
#define FIRE_BALL_BOUNCE_SPEED 0.2f


#define FIRE_BALL_BBOX_WIDTH 8
#define FIRE_BALL_BBOX_HEIGHT 8

#define FIRE_BALL_STATE_MARIO_SHOOT 100
#define FIRE_BALL_STATE_ENEMY_SHOOT 200
#define FIRE_BALL_STATE_FPP_SHOOT_NEAR 400
#define FIRE_BALL_STATE_FPP_SHOOT_FAR 500
#define FIRE_BALL_DISAPPEAR 300

#define ID_ANI_FIRE_BALL 100
#define ID_ANI_FIRE_BALL_DISAPPEAR 115

#define	FIRE_BALL_FPP_SHOOT_SPEED_Y 0.03f
#define FIRE_BALL_FPP_SHOOT_SPEED_X_NEAR 0.03f
#define FIRE_BALL_FPP_SHOOT_SPEED_X_FAR 0.08f

#define ADJUST_FPP_SHOOT_FIRE_BALL_HEIGHT 10

#define DISAPPEAR_EFFECT_TIME_OUT 200

class CFireBall : public CGameObject
{
protected:
	float ax;
	float ay;
	int mario_nx;
	BOOLEAN isDisappear = false;
	ULONGLONG start_disappear;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable();
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFireBall(float x, float y);
	virtual void SetState(int state);
};

