#include "EffectScore.h"
#include "Mario.h"
#include "PlayScene.h"

CEffectScore::CEffectScore(float x, float y, int model) : CGameObject(x, y)
{

	this->ay = 0;
	this->ax = 0;
	this->x = x;
	this->y = y;
	this->model = model;
	minY = y - SCORE_EFFECT_MAX_HEIGHT;
	this->vy = -SCORE_EFFECT_SPEED;
}

void CEffectScore::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CEffectScore::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		isDeleted = true;
	}
	if (isDeleted) {
		SetScoreMario();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CEffectScore::Render()
{
	int aniId = ID_ANI_SCORE_EFFECT_100;
	switch (model) {
	case SCORE_EFFECT_100:
		aniId = ID_ANI_SCORE_EFFECT_100;
		break;
	case SCORE_EFFECT_200:
		aniId = ID_ANI_SCORE_EFFECT_200;
		break;
	case SCORE_EFFECT_400:
		aniId = ID_ANI_SCORE_EFFECT_400;
		break;
	case SCORE_EFFECT_800:
		aniId = ID_ANI_SCORE_EFFECT_800;
		break;
	case SCORE_EFFECT_1000:
		aniId = ID_ANI_SCORE_EFFECT_1000;
		break;
	case SCORE_EFFECT_2000:
		aniId = ID_ANI_SCORE_EFFECT_2000;
		break;
	case SCORE_EFFECT_4000:
		aniId = ID_ANI_SCORE_EFFECT_4000;
		break;
	case SCORE_EFFECT_8000:
		aniId = ID_ANI_SCORE_EFFECT_8000;
		break;
	case EFFECT_1_UP:
		aniId = ID_ANI_SCORE_EFFECT_1_UP;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CEffectScore::SetScoreMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (model) {
	case SCORE_EFFECT_100:
		mario->SetScore(mario->GetScore() + 100);
		break;
	case SCORE_EFFECT_200:
		mario->SetScore(mario->GetScore() + 200);
		break;
	case SCORE_EFFECT_400:
		mario->SetScore(mario->GetScore() + 400);
		break;
	case SCORE_EFFECT_800:
		mario->SetScore(mario->GetScore() + 800);
		break;
	case SCORE_EFFECT_1000:
		mario->SetScore(mario->GetScore() + 1000);
		break;
	case SCORE_EFFECT_2000:
		mario->SetScore(mario->GetScore() + 2000);
		break;
	case SCORE_EFFECT_4000:
		mario->SetScore(mario->GetScore() + 4000);
		break;
	case SCORE_EFFECT_8000:
		mario->SetScore(mario->GetScore() + 8000);
		break;
	case EFFECT_1_UP:
		mario->SetHealth(mario->GetHealth() + 1);
	}
}
