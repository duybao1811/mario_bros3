#pragma once
#include "GameObject.h"

#define ARROW_ANI_ID 6

class CArrow : public CGameObject
{
public:
	CArrow(float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	~CArrow();
};

