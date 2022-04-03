#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Koopas.h"
#include "Coin.h"
#include "Portal.h"
#include "FireBall.h"
#include "Collision.h"
#include "QuestionBrick.h"
#include "Leaf.h"
#include "MushRoom.h"
#include "Flower.h"
#include "define.h"
#include "EffectScore.h"
#include "GoldBrick.h"
#include "PButton.h"
#include "PlayScene.h"
#include "Pipe.h"
#include "ColorBlock.h"
#include "Tail.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy += ay * dt;
	vx += ax * dt + nx * powerStack * ax;
	
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (x <= MARIO_BIG_BBOX_WIDTH) {
		x = MARIO_BIG_BBOX_WIDTH;
	}
	if (x + MARIO_BIG_BBOX_WIDTH >= scene->map->GetMapWidth()) {
		x = (float)(scene->map->GetMapWidth() - MARIO_BIG_BBOX_WIDTH);
	}
	if (y <= 0) {
		y = 0;
	}

	//limit move x
	if (abs(vx) > MARIO_WALKING_SPEED) {
		if (!isRunning) {
			vx = nx * MARIO_WALKING_SPEED;
		}
		else {
			if (abs(vx) >= MARIO_RUNNING_SPEED) {
				if (powerStack < MARIO_POWER_FULL) {
					vx = nx * MARIO_RUNNING_SPEED;
				}
				else {
					vx = nx * MARIO_RUNNING_MAX_SPEED;
				}
			}
		}
	}

	if (vx < 0 && nx > 0 && !isWalking)
	{
		vx = 0;
		ax = 0;
	}
	if (vx > 0 && nx < 0 && !isWalking)
	{
		vx = 0;
		ax = 0;
	}

	//limit move y
	if (vy <= -MARIO_JUMP_SPEED_MAX && !isRunningMax) {
		vy = -MARIO_JUMP_SPEED_MAX;
		ay = MARIO_GRAVITY;
	}

	if (vy <= -MARIO_JUMP_RUN_SPEED_Y && isRunningMax) {
		vy = -MARIO_JUMP_RUN_SPEED_Y;
		ay = MARIO_GRAVITY;
	}
	//change direction when run max speed

		
	if (level == MARIO_LEVEL_RACCOON && vy > 0) {
		canFallSlow = true;
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (vy < 0) {
		isOnPlatform = false;
	}

	if (GetTickCount64() - running_start > POWER_STACK_TIME && isRunning && !isHoldTurtle)
	{
		running_start = GetTickCount64();
		powerStack++;
		if (powerStack > MARIO_POWER_FULL)
		{
			powerStack = MARIO_POWER_FULL;
			isRunningMax = true;
		}
		DebugOut(L"[INFO] powerStack! %d \n", powerStack);
	}

	if (GetTickCount64() - running_stop > POWER_STACK_LOST_TIME && powerStack && !isRunning)
	{
		running_stop = GetTickCount64();
		isRunningMax = false;
		powerStack--;
		if (powerStack <= 0)
		{
			powerStack = 0;
		}
		DebugOut(L"[INFO] powerStack! %d \n", powerStack);
	}

	if (GetTickCount64() - flying_start > LIMIT_MARIO_RACCOON_FLY_TIME && isFlying)
	{
		isFlying = false;
		isFlapping = false;
		canFallSlow = true;
		DebugOut(L"[INFO] mario raccoon fly time end\n");
	}

	if (GetTickCount64() - kick_start > MARIO_KICK_TIMEOUT && isKicking) {
		isKicking = false;
		kick_start = -1;
	}

	if (level == MARIO_LEVEL_BIG && GetTickCount64() - transform_start > MARIO_TRANSFORM_TIME_OUT && isTransform)
	{
		isTransform = false;
		transform_start = -1;
	}

	if (level == MARIO_LEVEL_RACCOON && GetTickCount64() - transform_start > MARIO_RACCOON_TRANSFORM_TIME_OUT && isTransform)
	{
		isTransform = false;
		transform_start = -1;
	}

	if (isAttack && GetTickCount64() - attack_start > MARIO_RACCON_ATTACK_TIME_OUT) {
		isAttack = false;
		attack_start = -1;
		tail = NULL;
	}

	if (isAttack) {
		SetTail();
	}

	if (isTransform) {
		ay = 0;
		vx = 0;
	}

	if (isAdjustHeight) {
		y -= ADJUST_HEIGHT_MARIO_SMALL_TRANSFORM_BIG;
		isAdjustHeight = false;
	}

	if (GetTickCount64() - shoot_start > MARIO_FIRE_TIME_SHOOT_EFFECT && canShoot) {
		shoot_start = -1;
		canShoot = false;
	}

	
	if (isGoThroughBlockColor) {
		y -= ADJUST_MARIO_COLLISION_WITH_COLOR_BLOCK;
		vy = -MARIO_JUMP_SPEED_MAX;
		isGoThroughBlockColor = false;
	}

	if (isShooting && level == MARIO_LEVEL_FIRE)
	{
		if (ListFire.size() < MARIO_FIRE_BALL_LIMIT)
		{
			ShootFire();
			canShoot = true;
			isShooting = false;
		}
	}
	if (tail) {
		tail->Update(dt, coObjects);
	}

	for (size_t i = 0; i < ListFire.size(); i++)
	{
		ListFire[i]->Update(dt, coObjects);
		if (ListFire[i]->isDeleted) {
			ListFire.erase(ListFire.begin() + i);
		}
	}

	for (size_t i = 0; i < ListEffect.size(); i++)
	{
		ListEffect[i]->Update(dt, coObjects);
		if (ListEffect[i]->isDeleted) {
			ListEffect.erase(ListEffect.begin() + i);
		}
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{	
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		if (e->ny < 0 ) {
			isOnPlatform = true;
			isFlying = false;
			canFallSlow = false;
			vy = 0;
		}
		else {
			vy = 0;
			ay = MARIO_GRAVITY;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking()) {
		if (e->obj->GetType() == OBJECT || e->obj->GetType() == GOLDBRICK) {
			SetState(MARIO_STATE_RELEASE_RUN);
		}
	}

	if (e->obj->GetType() == COIN) {
		coin++;
		score += 100;
		e->obj->Delete();
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);

	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CFlower*>(e->obj))
		OnCollisionWithFlower(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CGoldBrick*>(e->obj))
		OnCollisionWithGoldBrick(e);
	else if (dynamic_cast<CMushRoom*>(e->obj))
		OnCollisionWithMushRoom(e);
	else if (dynamic_cast<PButton*>(e->obj))
		OnCollisionWithPButton(e);
	else if (dynamic_cast<CColorBlock*>(e->obj))
		OnCollisionWithColorBlock(e);
}

void CMario::OnCollisionWithColorBlock(LPCOLLISIONEVENT e) {

	if (e->ny > 0) {
		isGoThroughBlockColor = true;
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			if (goomba->GetModel() == GOOMBA_BASE) {
				goomba->SetState(GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				obj = new CEffectScore(goomba->GetX(),goomba->GetY(), SCORE_EFFECT_100);
				ListEffect.push_back(obj);
			}
			else
				if (goomba->GetState() == GOOMBA_STATE_WALKING) {
					goomba->SetState(GOOMBA_STATE_DIE);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
					obj = new CEffectScore(goomba->GetX(), goomba->GetY(), SCORE_EFFECT_100);
					ListEffect.push_back(obj);
				}
				else {
					goomba->SetState(GOOMBA_STATE_WALKING);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
					obj = new CEffectScore(goomba->GetX(), goomba->GetY(), SCORE_EFFECT_100);
					ListEffect.push_back(obj);
				}
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				SetHurt();
			}
		}
	}

}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	if (e->ny < 0)
	{
		if (koopas->GetState() == KOOPAS_STATE_WALKING || koopas->GetState() == KOOPAS_STATE_IS_KICKED)
		{
			koopas->SetState(KOOPAS_STATE_DEFEND);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			obj = new CEffectScore(koopas->GetX(), koopas->GetY(), SCORE_EFFECT_100);
			ListEffect.push_back(obj);
		}
		else if (koopas->GetState() == KOOPAS_STATE_JUMP) {
			koopas->SetState(KOOPAS_STATE_WALKING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			obj = new CEffectScore(koopas->GetX(), koopas->GetY(), SCORE_EFFECT_100);
			ListEffect.push_back(obj);
		}
		else if (koopas->GetState() == KOOPAS_STATE_DEFEND)
		{
			koopas->SetState(KOOPAS_STATE_IS_KICKED);
			obj = new CEffectScore(koopas->GetX(), koopas->GetY(), SCORE_EFFECT_100);
			ListEffect.push_back(obj);
		}
	}
	else if (e->nx != 0)
	{
		if (koopas->GetState() == KOOPAS_STATE_DEFEND || koopas->GetState() == KOOPAS_STATE_UPSIDE) {
			if (isRunning && !isHoldTurtle) {
				isHoldTurtle = true;
				isKicking = false;
				powerStack = 0;
				koopas->isHeld = true;
			}
			else {
				SetState(MARIO_STATE_KICK);
				koopas->SetState(KOOPAS_STATE_IS_KICKED);
			}
		}
		else {
			SetHurt();
		}
	}
	else if (e->ny > 0) {
		SetHurt();
	}
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e) {
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->ny > 0 && !questionBrick -> isEmpty) {
		questionBrick->SetState(QUESTION_BRICK_STATE_UP);
	}
}

void CMario::OnCollisionWithGoldBrick(LPCOLLISIONEVENT e) {
	CGoldBrick* goldBrick = dynamic_cast<CGoldBrick*>(e->obj);
		if (e->ny > 0 && !goldBrick->isEmpty) {
			goldBrick->SetState(GOLD_BRICK_STATE_UP);
	}

}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	transform_start = GetTickCount64();
	isTransform = true;
	level = MARIO_LEVEL_RACCOON;
	obj = new CEffectScore(x, y, SCORE_EFFECT_1000);
	ListEffect.push_back(obj);
	e->obj->Delete();
}
void CMario::OnCollisionWithMushRoom(LPCOLLISIONEVENT e)
{
	if (e->obj->GetModel() == RED_MUSHROOM) {
		transform_start = GetTickCount64();
		isTransform = true;
		isAdjustHeight = true;
		level = MARIO_LEVEL_BIG;
		obj = new CEffectScore(x, y, SCORE_EFFECT_1000);
		ListEffect.push_back(obj);
		e->obj->Delete();
	}
	else if (e->obj->GetModel() == GREEN_MUSHROOM) {
		obj = new CEffectScore(x, y, EFFECT_1_UP);
		ListEffect.push_back(obj);
		e->obj->Delete();
	}
}

void CMario::OnCollisionWithFlower(LPCOLLISIONEVENT e)
{
	level = MARIO_LEVEL_FIRE;
	obj = new CEffectScore(x, y, SCORE_EFFECT_1000);
	ListEffect.push_back(obj);
	e->obj->Delete();
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithPButton(LPCOLLISIONEVENT e)
{
	PButton* button = dynamic_cast<PButton*>(e->obj);
	if (e->ny < 0) {
		button->SetIsPressed(true);
		button->SetGoldBrickTransform(true);
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isRunningMax)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (vy < 0) {
				if (isHoldTurtle) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT;
					else
						aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT;
				}
				else {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
				}
			}
			else {
				if (isHoldTurtle) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT;
					else
						aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT;
				}
				else {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_SMALL_FALL_RIGHT;
					else
						aniId = ID_ANI_MARIO_SMALL_FALL_LEFT;
				}
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (isKicking) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
		}
		else if (isHoldTurtle) {
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT;
			}
			else if (vx > 0) {
				aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT;
			}
			else {
				aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT;
			}
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (nx < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (isRunningMax)
					aniId = ID_ANI_MARIO_SMALL_RUN_MAX_RIGHT;
				else if (isRunning)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (isRunningMax)
					aniId = ID_ANI_MARIO_SMALL_RUN_MAX_LEFT;
				else if (isRunning)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isRunningMax)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (vy < 0) {
				if (isHoldTurtle) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_HOLD_JUMP_RIGHT;
					else
						aniId = ID_ANI_MARIO_HOLD_JUMP_LEFT;
				}
				else {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
				}
				
			}
			else {
				if (isHoldTurtle) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_HOLD_JUMP_RIGHT;
					else
						aniId = ID_ANI_MARIO_HOLD_JUMP_LEFT;
				}
				else {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_FALL_RIGHT;
				else
					aniId = ID_ANI_MARIO_FALL_LEFT;
				}
			}
		}

	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else if (isKicking) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_KICK_LEFT;
		}
		else if (isTransform) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_TRANSFORM_RIGHT;
			else
				aniId = ID_ANI_MARIO_TRANSFORM_LEFT;

		}
		else if (isHoldTurtle) {
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_HOLD_IDLE_LEFT;
			}
			else if (vx > 0) {
				aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT;
			}
			else {
				aniId = ID_ANI_MARIO_HOLD_WALK_LEFT;
			}
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (nx < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (isRunningMax)
					aniId = ID_ANI_MARIO_RUN_MAX_RIGHT;
				else if (isRunning)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (isRunningMax)
					aniId = ID_ANI_MARIO_RUN_MAX_LEFT;
				else if (isRunning)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}
		}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for RACCOON Mario
//
int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isFlying && isFlapping) {
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_FLY_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_FLY_LEFT;
		}
		else if (isRunningMax)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
		}
		else if (isAttack) {
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_ATTACK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_ATTACK_LEFT;
		}
		else
		{
			if (isHoldTurtle) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_HOLD_JUMP_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_HOLD_JUMP_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
			}
		}

		if (vy > 0) {
			if (isAttack) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_RACCOON_ATTACK_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_ATTACK_LEFT;
			}
			else {
				if (!isFlying) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_RACCOON_FALL_RIGHT;
					else
						aniId = ID_ANI_MARIO_RACCOON_FALL_LEFT;
				}
				else {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_RACCOON_FALL_FLY_RIGHT;
					else
						aniId = ID_ANI_MARIO_RACCOON_FALL_FLY_LEFT;
				}

				if (isFallSlowing) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_RACCOON_FALL_SLOW_RIGHT;
					else
						aniId = ID_ANI_MARIO_RACCOON_FALL_SLOW_LEFT;
				}
				if (isHoldTurtle) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_RACCOON_HOLD_JUMP_RIGHT;
					else
						aniId = ID_ANI_MARIO_RACCOON_HOLD_JUMP_LEFT;
				}
			}
			
		}

	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else if (isAttack) {
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_ATTACK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_ATTACK_LEFT;
		}
		else if (isKicking) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_KICK_LEFT;
		}
		else if (isTransform) {
				aniId = ID_ANI_MARIO_RACCOON_TRANSFORM;
		}
		else if (isHoldTurtle) {
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_HOLD_IDLE_LEFT;
			}
			else if (vx > 0) {
				aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_RIGHT;
			}
			else {
				aniId = ID_ANI_MARIO_RACCOON_HOLD_WALK_LEFT;
			}
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (nx < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (isRunningMax)
					aniId = ID_ANI_MARIO_RACCOON_RUN_MAX_RIGHT;
				else if (isRunning)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;

			}
			else // vx < 0
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (isRunningMax)
					aniId = ID_ANI_MARIO_RACCOON_RUN_MAX_LEFT;
				else if (isRunning)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}
		}

	if (aniId == -1)
		aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for FIRE Mario
//
int CMario::GetAniIdFire()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (isRunningMax)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_FIRE_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_FIRE_JUMP_RUN_LEFT;
		}
		else
		{
			if (vy < 0) {
				if (isHoldTurtle) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_FIRE_HOLD_JUMP_RIGHT;
					else
						aniId = ID_ANI_MARIO_FIRE_HOLD_JUMP_LEFT;
				}
				else {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_FIRE_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_FIRE_JUMP_WALK_LEFT;
				}
			}
			else {
				if (isHoldTurtle) {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_FIRE_HOLD_JUMP_RIGHT;
					else
						aniId = ID_ANI_MARIO_FIRE_HOLD_JUMP_LEFT;
				}
				else {
					if (nx >= 0)
						aniId = ID_ANI_MARIO_FIRE_FALL_RIGHT;
					else
						aniId = ID_ANI_MARIO_FIRE_FALL_LEFT;
				}
				
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_FIRE_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_FIRE_SIT_LEFT;
		}
		else if (isKicking) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_FIRE_KICK_RIGHT;
			else
				aniId = ID_ANI_MARIO_FIRE_KICK_LEFT;
		}
		else if (canShoot) {
			if (nx > 0) {
				aniId = ID_ANI_MARIO_FIRE_SHOOT_FIRE_RIGHT;
			}
			else
				aniId = ID_ANI_MARIO_FIRE_SHOOT_FIRE_LEFT;
		}
		else if (isHoldTurtle) {
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_FIRE_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_FIRE_HOLD_IDLE_LEFT;
			}
			else if (vx > 0) {
				aniId = ID_ANI_MARIO_FIRE_HOLD_WALK_RIGHT;
			}
			else {
				aniId = ID_ANI_MARIO_FIRE_HOLD_WALK_LEFT;
			}
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_FIRE_IDLE_RIGHT;
				else
					aniId = ID_ANI_MARIO_FIRE_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (nx < 0)
					aniId = ID_ANI_MARIO_FIRE_BRACE_RIGHT;
				else if (isRunningMax)
					aniId = ID_ANI_MARIO_FIRE_RUN_MAX_RIGHT;
				else if (isRunning)
					aniId = ID_ANI_MARIO_FIRE_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_FIRE_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_FIRE_BRACE_LEFT;
				else if (isRunningMax)
					aniId = ID_ANI_MARIO_FIRE_RUN_MAX_LEFT;
				else if (isRunning)
					aniId = ID_ANI_MARIO_FIRE_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_FIRE_WALKING_LEFT;
			}
		}

	if (aniId == -1)
		aniId = ID_ANI_MARIO_FIRE_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();
	else if (level == MARIO_LEVEL_FIRE)
		aniId = GetAniIdFire();

	for (int i = 0; i < ListFire.size(); i++)
	{
		ListFire[i]->Render();
	}

	for (int i = 0; i < ListEffect.size(); i++)
	{
		ListEffect[i]->Render();
	}

	if (tail) {
		tail->Render();
	}

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();

	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		running_start = GetTickCount64();
		nx = 1;
		isRunning = true;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		running_start = GetTickCount64();
		nx = -1;
		isRunning = true;
		break;
	case MARIO_STATE_RELEASE_RUN:
		isRunning = false;
		running_stop = GetTickCount64();
		break;
	case MARIO_STATE_WALKING_RIGHT:
		ax = MARIO_ACCEL_WALK_X;
		isWalking = true;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		ax = -MARIO_ACCEL_WALK_X;
		isWalking = true;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:

		if (isOnPlatform) {

			if (vy > -MARIO_JUMP_SPEED_MIN)
			{
				vy = -MARIO_JUMP_SPEED_MIN;
			}
			if (isRunningMax)
			{
				vy = -MARIO_JUMP_RUN_SPEED_Y;

				if (level == MARIO_LEVEL_RACCOON) {
					isFlying = true;
					flying_start = GetTickCount64();
				}
			}
			ay = -MARIO_ACCEL_JUMP_Y;
		}
		break;
	case MARIO_RACCOON_STATE_FLAPPING:
		ay = -MARIO_RACCOON_FLAPPING_SPEED;
		isFlapping = true;
		break;
	case MARIO_RACCOON_STATE_FALL_SLOW:
		isFallSlowing = true;
		vy = -MARIO_RACCOON_FALL_SLOW_SPEED;
		break;
	case MARIO_STATE_KICK:
		isKicking = true;
		kick_start = GetTickCount64();
		break;
	case MARIO_RACCOON_STATE_ATTACK:
		attack_start = GetTickCount64();
		isAttack = true;

		break;
	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			Decelerate();
			vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	case MARIO_STATE_SHOOTING:
		isShooting = true;
		shoot_start = GetTickCount64();
		break;
	case MARIO_STATE_IDLE:
		Decelerate();
		ay = MARIO_GRAVITY;
		isWalking = false;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::SetHurt() {
	if (level > MARIO_LEVEL_SMALL)
	{
		level--;
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}

void CMario::Decelerate()
{
	if (vx > 0)
	{
		ax = -MARIO_DECELERATE_SPEED;
	}
	if (vx < 0)
	{
		ax = MARIO_DECELERATE_SPEED;
	}
}

void CMario::ShootFire()
{
	CFireBall* fireBall = new CFireBall(x + ADJUST_MARIO_SHOOT_FIRE_X, y + ADJUST_MARIO_SHOOT_FIRE_Y);
	fireBall->SetState(FIRE_BALL_STATE_MARIO_SHOOT);
	ListFire.push_back(fireBall);
}

void CMario::SetTail() {

	if (!tail) {
		tail = new CTail(x, y);
	}

	int timeAttack = (int)(GetTickCount64() - attack_start);

	// animation đầu tiên và cuối cùng của đánh đuôi set vị trí
	if ((timeAttack > 0 && timeAttack < MARIO_RACCON_ATTACK_TIME_OUT / NUM_OF_EFFECT_MARIO_RACCOON_ATTACK) || (timeAttack >= (MARIO_RACCON_ATTACK_TIME_OUT * 4 / NUM_OF_EFFECT_MARIO_RACCOON_ATTACK) && timeAttack < MARIO_RACCON_ATTACK_TIME_OUT)) {
		if (nx > 0)
		{
			tail->SetPosition(x - TAIL_BBOX_WIDTH / 2, y + POSITION_Y_OF_TAIL_MARIO / 2 - TAIL_BBOX_HEIGHT / 2);
		}
		else {
			tail->SetPosition(x + MARIO_BIG_BBOX_WIDTH - TAIL_BBOX_WIDTH / 2, y + POSITION_Y_OF_TAIL_MARIO / 2 - TAIL_BBOX_HEIGHT / 2);
		}
		tail->SetWidth(TAIL_BBOX_WIDTH);
		tail->SetHeight(TAIL_BBOX_HEIGHT);
	}

	// animation thứ hai của đánh đuôi set vị trí
	if (timeAttack >= (MARIO_RACCON_ATTACK_TIME_OUT * 1 / NUM_OF_EFFECT_MARIO_RACCOON_ATTACK) && timeAttack < (MARIO_RACCON_ATTACK_TIME_OUT * 2 / NUM_OF_EFFECT_MARIO_RACCOON_ATTACK)) {
		tail->SetWidth(0);
		tail->SetHeight(0);
	}

	// animation thứ ba của đánh đuôi set vị trí

	if (timeAttack >= (MARIO_RACCON_ATTACK_TIME_OUT * 2 / NUM_OF_EFFECT_MARIO_RACCOON_ATTACK) && timeAttack < (MARIO_RACCON_ATTACK_TIME_OUT * 3 / NUM_OF_EFFECT_MARIO_RACCOON_ATTACK)) {
		if (nx > 0) {
			tail->SetPosition(x + MARIO_BIG_BBOX_WIDTH - TAIL_BBOX_WIDTH / 2, y + POSITION_Y_OF_TAIL_MARIO / 2 - TAIL_BBOX_HEIGHT / 2);
		}
		else {
			tail->SetPosition(x - TAIL_BBOX_WIDTH / 2, y + POSITION_Y_OF_TAIL_MARIO / 2 - TAIL_BBOX_HEIGHT / 2);
		}
		tail->SetWidth(TAIL_BBOX_WIDTH);
		tail->SetHeight(TAIL_BBOX_HEIGHT);
	}
	// animation thứ tư của đánh đuôi set vị trí
	if (timeAttack >= (MARIO_RACCON_ATTACK_TIME_OUT * 3 / NUM_OF_EFFECT_MARIO_RACCOON_ATTACK) && timeAttack < (MARIO_RACCON_ATTACK_TIME_OUT * 4 / NUM_OF_EFFECT_MARIO_RACCOON_ATTACK)) {
		tail->SetWidth(0);
		tail->SetHeight(0);
	}

}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level != MARIO_LEVEL_SMALL)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}