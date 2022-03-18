#include "Tail.h"
#include "define.h"
#include "GoldBrick.h"
#include "QuestionBrick.h"
#include "debug.h"
#include "EffectAttack.h"
#include "PlayScene.h"

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - width / 2;
	right = x + width;
	top = y - height / 2;
	bottom = y + height;
}

void CTail::OnCollisionWithGoldBrick(LPGAMEOBJECT& e)
{
	CGoldBrick* goldbrick = dynamic_cast<CGoldBrick*>(e);
	goldbrick->SetBreak(true);	
}

void CTail::OnCollisionWithQuestionBrick(LPGAMEOBJECT& e)
{
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e);
	if (!questionBrick->isEmpty) {
		questionBrick->SetState(QUESTION_BRICK_STATE_UP);
	}
}

void CTail::OnCollisionWithEnemy(LPGAMEOBJECT& e)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->GetDirection() > 0) {
		CEffectAttack* effect = new CEffectAttack(x + width / 2, y);
		effect->SetState(EFFECT_ATTACK_STATE_SHOW);
		effects.push_back(effect);
	}
	else {
		CEffectAttack* effect = new CEffectAttack(x - width / 2, y);
		effect->SetState(EFFECT_ATTACK_STATE_SHOW);
		effects.push_back(effect);
	}

	e->SetState(ENEMY_STATE_IS_TAIL_ATTACKED);
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (CCollision::GetInstance()->CheckAABB(this, coObjects->at(i)))
		{
			if (coObjects->at(i)->GetType() == ENEMY) {
				OnCollisionWithEnemy(coObjects->at(i));
			}
			else if (dynamic_cast<CGoldBrick*>(coObjects->at(i)))
				OnCollisionWithGoldBrick(coObjects->at(i));
			else if (dynamic_cast<CQuestionBrick*>(coObjects->at(i)))
				OnCollisionWithQuestionBrick(coObjects->at(i));
		}
	}

	for (size_t i = 0; i < effects.size(); i++)
	{
		effects[i]->Update(dt, coObjects);
		if (effects[i]->isDeleted) {
			effects.erase(effects.begin() + i);
		}
	}
}

void CTail::Render() {
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Render();
	}
}