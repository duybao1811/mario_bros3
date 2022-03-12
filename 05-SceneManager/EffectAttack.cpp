#include "EffectAttack.h"
#include "PlayScene.h"

CEffectAttack::CEffectAttack(float x, float y) : CGameObject(x, y)
{

	this->ay = 0;
	this->ax = 0;
	this->x = x;
	this->y = y;
}

void CEffectAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - effect_start > EFFECT_ATTACK_TIME_OUT) {
		effect_start = -1;
		isDeleted = true;
	}
	CGameObject::Update(dt, coObjects);
}

void CEffectAttack::Render() {
	CAnimations::GetInstance()->Get(ID_ANI_EFFECT_ATTACK)->Render(x, y);
}

void CEffectAttack::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case EFFECT_ATTACK_STATE_SHOW:
		effect_start = GetTickCount64();

		break;
	}
}