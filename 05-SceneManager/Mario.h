#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "define.h"
#include "debug.h"
#include "Tail.h"
#include "AssetIDs.h"

class CMario : public CGameObject
{

	BOOLEAN isGoThroughBlockColor = false;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int untouchable; 
	ULONGLONG untouchable_start;

	int coin;
	int score;
	int health;
	int level;

	CGameObject* obj = NULL;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoldBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithFlower(LPCOLLISIONEVENT e);
	void OnCollisionWithPButton(LPCOLLISIONEVENT e);
	void OnCollisionWithColorBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithFireball(LPCOLLISIONEVENT e);


	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();
	int GetAniIdFire();
	void ShootFire();
	void SetTail();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		health = 0;
		score = 0;
		isRunningMax = false;
		SetType(EType::MARIO);
		this->x = x;
		this->y = y;
		tail = new CTail(x,y);
	}

	// DEFINE BOOLEAN VARIABLE
	BOOLEAN isSitting = false;
	BOOLEAN isOnPlatform = false;
	BOOLEAN isRunning = false;
	BOOLEAN isRunningMax = false;
	BOOLEAN isFlying = false;
	BOOLEAN isFlapping = false;
	BOOLEAN canFallSlow = false;
	BOOLEAN isFallSlowing = false;
	BOOLEAN isBlocked = false;
	BOOLEAN isFallNormal = false;
	BOOLEAN isWalking = false;
	BOOLEAN isKicking = false;
	BOOLEAN isShooting = false;
	BOOLEAN isHoldTurtle = false;
	BOOLEAN canShoot = false;
	BOOLEAN isTransform = false;
	BOOLEAN isAdjustHeight = false; //adjust height when transform
	BOOLEAN isJumping = false;
	BOOLEAN isAttack = false;
	int powerStack = 0;


	// TIME
	ULONGLONG running_start = -1;
	ULONGLONG running_stop = -1;
	ULONGLONG flying_start = -1;
	ULONGLONG kick_start = -1;
	ULONGLONG shoot_start = -1;
	ULONGLONG transform_start = -1;
	ULONGLONG attack_start = -1;

	vector<LPGAMEOBJECT> ListFire;
	vector<LPGAMEOBJECT> ListEffect;
	CTail* tail;

	void SetIsRunning(BOOLEAN run) { isRunning = run; }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	void Decelerate();

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return level; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetHurt();

	int GetScore() { return score; }
	int GetCoin() { return coin; }
	int GetHealth() { return health; }

	void SetScore(int _score) { score = _score; }
	void SetCoin(int _coin) { coin = _coin; }
	void SetHealth(int _health) { health = _health; }
};