#include "ColorBlock.h"
#include "Pipe.h"
#include "define.h"
#include "Mario.h"
#include "PlayScene.h"
#include "debug.h"

CColorBlock::CColorBlock(float x, float y, float width, float height) : CGameObject(x, y) {

	this->width = width;
	this->height = height;
}

void CColorBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - width / 2;
	right = left + width;
	top = y - height / 2;
	bottom = top + height;
}