#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "define.h"
#include "debug.h"
#include "Tail.h"
#include "AssetIDs.h"


// SPEED
#pragma region MARIO_SPEED
#define MARIO_WALKING_SPEED_MAX 0.1f
#define MARIO_WALKING_SPEED		0.08f
#define MARIO_DECELERATE_SPEED 0.00012f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_RUNNING_MAX_SPEED 0.3f

#define MARIO_ACCEL_WALK_X	0.00015f
#define MARIO_ACCEL_RUN_X	0.00025f

#define MARIO_JUMP_RUN_SPEED_Y	0.5f
#define MARIO_ACCEL_JUMP_Y 0.0005f
#define MARIO_JUMP_SPEED_MIN 0.18f
#define MARIO_JUMP_SPEED_MAX 0.28f

#define MARIO_RACCOON_FLAPPING_SPEED 0.002f
#define MARIO_RACCOON_FALL_SLOW_SPEED 0.03f

#define MARIO_GRAVITY			0.0015f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define ADJUST_MARIO_COLLISION_WITH_COLOR_BLOCK 1
#pragma endregion
// STATE

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500
#define MARIO_STATE_RELEASE_RUN 401
#define MARIO_STATE_KICK 402

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_RUN_MAX_SPEED 700

#define MARIO_RACOON_STATE_FLY 800
#define MARIO_RACCOON_STATE_FLAPPING 801
#define MARIO_RACCOON_STATE_FALL_SLOW 802

#define MARIO_STATE_SHOOTING 803
#define MARIO_STATE_FALL 302

#define MARIO_RACCOON_STATE_ATTACK 900


// LEVEL
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON 3
#define MARIO_LEVEL_FIRE 4

// BBOX
#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

// TIME
#define MARIO_UNTOUCHABLE_TIME 2500
#define POWER_STACK_TIME 250
#define POWER_STACK_LOST_TIME 250
#define LIMIT_MARIO_RACCOON_FLY_TIME 5000
#define MARIO_KICK_TIMEOUT 300
#define MARIO_FIRE_TIME_SHOOT_EFFECT 500
#define MARIO_DELAY_SHOOT 500
#define MARIO_TIME_DURING_SHOOT 300
#define MARIO_TRANSFORM_TIME_OUT 1000
#define MARIO_RACCOON_TRANSFORM_TIME_OUT 500
#define MARIO_RACCON_ATTACK_TIME_OUT 500

// Power stack

#define NUM_OF_EFFECT_MARIO_RACCOON_ATTACK 5 // số effect của raccoon quất đuôi tấn công

#define POSITION_Y_OF_TAIL_MARIO 18 //khoảng cách từ đầu mario đến vị trí đuôi
// fire ball
#define MARIO_FIRE_BALL_LIMIT 2

// ADJUST VALUE
#define ADJUST_HEIGHT_MARIO_SMALL_TRANSFORM_BIG 10
#define ADJUST_MARIO_SHOOT_FIRE_X 5
#define ADJUST_MARIO_SHOOT_FIRE_Y 5

#define SCORE_GET_COIN 100
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