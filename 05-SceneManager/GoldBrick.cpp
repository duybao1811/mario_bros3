#include "GoldBrick.h"
#include "PlayScene.h"
#include "MushRoom.h"
#include "PButton.h"
CGoldBrick::CGoldBrick(float x, float y, int model) :CGameObject(x, y)
{
	this->model = model;

	this->ay = 0;
	this->ax = 0;
	this->minY = y - GOLD_BRICK_BBOX_HEIGHT;
	this->startY = y;
	this->startX = x;

	SetType(EType::GOLDBRICK);
}

void CGoldBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - GOLD_BRICK_BBOX_WIDTH / 2;
	top = y - GOLD_BRICK_BBOX_HEIGHT / 2;
	right = left + GOLD_BRICK_BBOX_WIDTH;
	bottom = top + GOLD_BRICK_BBOX_HEIGHT;
}

void CGoldBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};


void CGoldBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		vy = GOLD_BRICK_SPEED_DOWN;
	}
	if (y > startY)
	{
		y = startY;
		vy = 0;
		isEmpty = true;
		isUnbox = true;
	}

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (isUnbox) {
		if (model == GOLD_BRICK_MUSHROOM) {
			CMushRoom* mushroom = new CMushRoom(x, y, GREEN_MUSHROOM);
			mushroom->SetState(MUSHROOM_STATE_UP);
			scene->objects.insert(scene->objects.begin() + 1, mushroom);
		}
		if (model == GOLD_BRICK_P_BUTTON) {
			PButton* button = new PButton(x, y - P_BUTTON_BBOX_HEIGHT);
			scene->objects.insert(scene->objects.begin() + 1, button);
		}
		isUnbox = false;
	}

	if (isTransform && GetTickCount64() - transform_start > 2000) {
		isTransform = false;
		transform_start = -1;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoldBrick::Render()
{
	int aniId = ID_ANI_GOLD_BRICK;

	if (model != GOLD_BRICK_COIN) {
		if (isEmpty) {
			aniId = ID_ANI_GOLD_BRICK_EMPTY;
		}
	}
	else {
		if (isTransform) {
			aniId = ID_ANI_COIN_IDLE;
		}
		else {
			aniId = ID_ANI_GOLD_BRICK;
		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGoldBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOLD_BRICK_STATE_UP:
			vy = -GOLD_BRICK_SPEED_UP;
			break;
		case GOLD_BRICK_STATE_TRANSFORM_COIN:
			transform_start = GetTickCount64();
			isTransform = true;
			if (type == GOLDBRICK) {
				SetType(EType::COIN);
			}
			break;
	}
}