#pragma once

#include "GameObject.h"
#include "define.h"
// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected: 
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
public: 
	CPlatform(float x, float y,
		float cell_width, float cell_height, int length) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		SetType(EType::OBJECT);
	}
	int GetLength() { return length; }
	void Render() {};//RenderBoundingBox();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 1; }
};

