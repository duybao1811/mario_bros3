#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "define.h"
#include "debug.h"

// SPEED
#pragma region MARIO_SPEED
#define MARIO_WALKING_SPEED_MAX 0.1f
#define MARIO_WALKING_SPEED		0.08f
#define MARIO_DECELERATE_SPEED 0.00012f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_RUNNING_MAX_SPEED 0.3f

#define MARIO_ACCEL_WALK_X	0.00015f
#define MARIO_ACCEL_RUN_X	0.00025f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f
#define MARIO_ACCEL_JUMP_Y 0.0005f
#define MARIO_JUMP_SPEED_MIN 0.18f
#define MARIO_JUMP_SPEED_MAX 0.3f

#define MARIO_RACCOON_FLAPPING_SPEED 0.0025f
#define MARIO_RACCOON_FALL_SLOW_SPEED 0.03f

#define MARIO_GRAVITY			0.0015f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

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


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 10001
#define ID_ANI_MARIO_IDLE_LEFT 10002

#define ID_ANI_MARIO_WALKING_RIGHT 10003
#define ID_ANI_MARIO_WALKING_LEFT 10004

#define ID_ANI_MARIO_RUNNING_RIGHT 10013
#define ID_ANI_MARIO_RUNNING_LEFT 10014

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 10005
#define ID_ANI_MARIO_JUMP_WALK_LEFT 10006

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 10015
#define ID_ANI_MARIO_JUMP_RUN_LEFT 10016

#define ID_ANI_MARIO_SIT_RIGHT 10011
#define ID_ANI_MARIO_SIT_LEFT 10012

#define ID_ANI_MARIO_RUN_MAX_RIGHT 10007
#define ID_ANI_MARIO_RUN_MAX_LEFT 10008

#define ID_ANI_MARIO_BRACE_RIGHT 10009
#define ID_ANI_MARIO_BRACE_LEFT 10010

#define ID_ANI_MARIO_FALL_RIGHT 10017
#define ID_ANI_MARIO_FALL_LEFT 10018

#define ID_ANI_MARIO_HOLD_IDLE_RIGHT 10019
#define ID_ANI_MARIO_HOLD_IDLE_LEFT 10020
#define ID_ANI_MARIO_HOLD_WALK_RIGHT 10021
#define ID_ANI_MARIO_HOLD_WALK_LEFT 10022
#define ID_ANI_MARIO_HOLD_JUMP_RIGHT 10025
#define ID_ANI_MARIO_HOLD_JUMP_LEFT 10026

#define ID_ANI_MARIO_KICK_RIGHT 10023
#define ID_ANI_MARIO_KICK_LEFT 10024

#define ID_ANI_MARIO_TRANSFORM_RIGHT 11027
#define ID_ANI_MARIO_TRANSFORM_LEFT 11028

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 11001
#define ID_ANI_MARIO_SMALL_IDLE_LEFT  11002

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 11003
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 11004

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 11012
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 11013

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 11010
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 11011

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 11005
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 11006

#define ID_ANI_MARIO_SMALL_RUN_MAX_RIGHT 11007
#define ID_ANI_MARIO_SMALL_RUN_MAX_LEFT	11008

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 11014
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 11015

#define ID_ANI_MARIO_SMALL_FALL_RIGHT 11016
#define ID_ANI_MARIO_SMALL_FALL_LEFT 11017

#define ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT 11018
#define ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT 11019
#define	ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT 11020
#define ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT 11021
#define ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT 11024
#define ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT 11025

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 11022
#define ID_ANI_MARIO_SMALL_KICK_LEFT 11023

// RACCOON

#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 12001
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 12002

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 12003
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 12004

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 12013
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 12014

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 12005
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 12006

#define ID_ANI_MARIO_RACCOON_RUN_MAX_RIGHT 12007
#define ID_ANI_MARIO_RACCOON_RUN_MAX_LEFT 12008

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT 12015
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT 12016

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 12011
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 12012

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 12009
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 12010

#define ID_ANI_MARIO_RACCOON_FALL_RIGHT 12017
#define ID_ANI_MARIO_RACCOON_FALL_LEFT 12018

#define ID_ANI_MARIO_RACCOON_HOLD_IDLE_RIGHT 12019
#define ID_ANI_MARIO_RACCOON_HOLD_IDLE_LEFT 12020
#define ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT 12021
#define ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT 12022
#define ID_ANI_MARIO_RACCOON_HOLD_JUMP_RIGHT 12031
#define ID_ANI_MARIO_RACCOON_HOLD_JUMP_LEFT	12032

#define ID_ANI_MARIO_RACCOON_KICK_RIGHT 12023
#define ID_ANI_MARIO_RACCOON_KICK_LEFT 12024

#define ID_ANI_MARIO_RACCOON_FLY_RIGHT 12025
#define ID_ANI_MARIO_RACCOON_FLY_LEFT 12026

#define ID_ANI_MARIO_RACCOON_FALL_FLY_RIGHT 12027
#define ID_ANI_MARIO_RACCOON_FALL_FLY_LEFT	12028

#define ID_ANI_MARIO_RACCOON_FALL_SLOW_RIGHT 12029
#define ID_ANI_MARIO_RACCOON_FALL_SLOW_LEFT	12030

#define ID_ANI_MARIO_RACCOON_TRANSFORM 115
// FIRE

#define ID_ANI_MARIO_FIRE_IDLE_RIGHT 13001
#define ID_ANI_MARIO_FIRE_IDLE_LEFT 13002

#define ID_ANI_MARIO_FIRE_WALKING_RIGHT 13003
#define ID_ANI_MARIO_FIRE_WALKING_LEFT 13004

#define ID_ANI_MARIO_FIRE_RUNNING_RIGHT 13013
#define ID_ANI_MARIO_FIRE_RUNNING_LEFT 13014

#define ID_ANI_MARIO_FIRE_JUMP_WALK_RIGHT 13005
#define ID_ANI_MARIO_FIRE_JUMP_WALK_LEFT 13006

#define ID_ANI_MARIO_FIRE_RUN_MAX_RIGHT 13007
#define ID_ANI_MARIO_FIRE_RUN_MAX_LEFT 13008

#define ID_ANI_MARIO_FIRE_JUMP_RUN_RIGHT 13015
#define ID_ANI_MARIO_FIRE_JUMP_RUN_LEFT 13016

#define ID_ANI_MARIO_FIRE_SIT_RIGHT 13011
#define ID_ANI_MARIO_FIRE_SIT_LEFT 13012

#define ID_ANI_MARIO_FIRE_BRACE_RIGHT 13009
#define ID_ANI_MARIO_FIRE_BRACE_LEFT 13010

#define ID_ANI_MARIO_FIRE_FALL_RIGHT 13017
#define ID_ANI_MARIO_FIRE_FALL_LEFT 13018

#define ID_ANI_MARIO_FIRE_HOLD_IDLE_RIGHT 13019
#define ID_ANI_MARIO_FIRE_HOLD_IDLE_LEFT 13020
#define ID_ANI_MARIO_FIRE_HOLD_WALK_RIGHT 13021
#define ID_ANI_MARIO_FIRE_HOLD_WALK_LEFT 13022
#define ID_ANI_MARIO_FIRE_HOLD_JUMP_RIGHT 13027
#define ID_ANI_MARIO_FIRE_HOLD_JUMP_LEFT 13028

#define ID_ANI_MARIO_FIRE_KICK_RIGHT 13023
#define ID_ANI_MARIO_FIRE_KICK_LEFT 13024

#define ID_ANI_MARIO_FIRE_SHOOT_FIRE_RIGHT 13025
#define ID_ANI_MARIO_FIRE_SHOOT_FIRE_LEFT 13026


#define ID_ANI_MARIO_DIE 999

#pragma endregion

#define GROUND_Y 160.0f



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
#define MARIO_RACCOON_TRANSFORM_TIME_OUT 300

// LIME VALUE
// Power stack
#define MARIO_POWER_FULL 7

// fire ball
#define MARIO_FIRE_BALL_LIMIT 2

// ADJUST VALUE
#define ADJUST_HEIGHT_MARIO_SMALL_TRANSFORM_BIG 10
#define ADJUST_MARIO_SHOOT_FIRE_X 5
#define ADJUST_MARIO_SHOOT_FIRE_Y 5

class CMario : public CGameObject
{

	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	
	int coin; 
	CGameObject* obj = NULL;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithFlower(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();
	int GetAniIdFire();
	void ShootFire();

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
		isRunningMax = false;
		SetType(EType::MARIO);
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
	int powerStack = 0;


	// TIME
	ULONGLONG running_start = -1;
	ULONGLONG running_stop = -1;
	ULONGLONG flying_start = -1;
	ULONGLONG kick_start = -1;
	ULONGLONG shoot_start = -1;
	ULONGLONG transform_start = -1;
	
	vector<LPGAMEOBJECT> ListFire;
	vector<LPGAMEOBJECT> ListEffect;
	int score = 0;
	int hearth = 0;

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
};