#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Font.h"

#define ID_ANI_HUD 300

class CHUD
{
	float x, y;
	ULONGLONG now_time;
	int time;
	CFont font;

public:
	CHUD(float x, float y);
	void Render(CMario* mario, int remainingTime);
	string FillNumber(string s, UINT fillNumber);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	~CHUD() {}
};

