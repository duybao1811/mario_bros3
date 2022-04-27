#include "WorldPlayer.h"
#include "AssetIDs.h"
#include "Backup.h"
#include "Door.h"
#include "BlockObj.h"
#include "debug.h"

CWorldPlayer::CWorldPlayer(float x, float y) : CGameObject()
{
	SetState(MARIO_WORLD_MAP_STATE_IDLE);
	this->x = x;
	this->y = y;
	this->ay = 0;
	this->ax = 0;
	this->level = CBackUp::GetInstance()->level;
}

void CWorldPlayer::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CWorldPlayer::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBlockObj*>(e->obj))
		OnCollisionWithBlockObj(e);
	if (dynamic_cast<CDoor*>(e->obj))
		OnCollisionWithDoor(e);
}

void CWorldPlayer::OnCollisionWithDoor(LPCOLLISIONEVENT e) 
{
	CDoor* door = dynamic_cast<CDoor*>(e->obj);
	vx = 0;
	vy = 0;
	DebugOut(L"[INFO] powerStack! %d \n", door->GetScene());
	sceneSwitch = door->GetScene();
}

void CWorldPlayer::OnCollisionWithBlockObj(LPCOLLISIONEVENT e)
{

}


void CWorldPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CWorldPlayer::Render() {
	int ani = ID_ANI_MARIO_SMALL_IN_WORLD_MAP;

	switch (level) {
		case MARIO_LEVEL_SMALL: {
			ani = ID_ANI_MARIO_SMALL_IN_WORLD_MAP;
			break;
		}
		case MARIO_LEVEL_BIG:
		{
			ani = ID_ANI_MARIO_IN_WORLD_MAP;
			break;
		}
		case MARIO_LEVEL_RACCOON:
		{
			ani = ID_ANI_MARIO_RACCOON_IN_WORLD_MAP;
			break;
		}
		case MARIO_LEVEL_FIRE:
		{
			ani = ID_ANI_MARIO_FIRE_IN_WORLD_MAP;
			break;
		}
	}

	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	RenderBoundingBox();
}


void CWorldPlayer::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MARIO_WORLD_MAP_STATE_IDLE:
	{
		vx = vy = 0;
		break;
	}
	case MARIO_WORLD_MAP_STATE_WALK_RIGHT:
	{
		vx = MARIO_WORLD_MAP_SPEED;
		vy = 0;
		break;
	}
	case MARIO_WORLD_MAP_STATE_WALK_LEFT: 
	{
		vx = -MARIO_WORLD_MAP_SPEED;
		vy = 0;
		break;
	}
	case MARIO_WORLD_MAP_STATE_WALK_TOP: 
	{
		vx = 0;
		vy = -MARIO_WORLD_MAP_SPEED;
		break;
	}
	case MARIO_WORLD_MAP_STATE_WALK_BOTTOM:
	{
		vx = 0;
		vy = MARIO_WORLD_MAP_SPEED;
		break;
	}
}
}