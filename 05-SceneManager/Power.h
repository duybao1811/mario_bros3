#pragma once
#include "GameObject.h"

#define POWER_ANI_ID 301
#define POWER_MAX_ANI_ID 302
#define POWER_WIDTH 8

class CPower : public CGameObject
{
	float x, y;
	int stack;
public:
	CPower(float x, float y, int stack);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	~CPower();
};

