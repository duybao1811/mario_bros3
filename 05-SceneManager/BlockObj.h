#pragma once
#include "GameObject.h"

#define BLOCK_OBJ_BBOX_WIDTH 8
#define BLOCK_OBJ_BBOX_HEIGHT 8

class CBlockObj : public CGameObject
{
public:
	CBlockObj(float x, float y) : CGameObject(x, y) {}
	virtual void Render() { RenderBoundingBox(); }
	void Update(DWORD dt) {};
	virtual int IsBlocking() { return 0; }
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

