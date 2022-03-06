#pragma once
#include "GameObject.h"

#define QUESTION_BRICK_BBOX_WIDTH 16
#define QUESTION_BRICK_BBOX_HEIGHT 16

#define ID_ANI_QUESTION_BRICK 102
#define ID_ANI_QUESTION_BRICK_EMPTY 103


#define QUESTION_BRICK_MAX_HEIGHT 10 
#define QUESTION_BRICK_SPEED_UP 0.1f

class CQuestionBrick : public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;
	float startY;
	// model = 1: ra tiền
	// model = 2: ra lá hoặc ra nấm đỏ hoặc ra hoa lửa tùy theo level mario
	
	int model;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);

public:
	CQuestionBrick(float x, float y, int model);
	virtual void SetState(int state);
	BOOLEAN isUnbox = false;
	BOOLEAN isEmpty = false;
};

