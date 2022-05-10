#pragma once

#include "GameObject.h"

#define PORTAL_TYPE_TO_EXTRA_SCENE	1
#define PORTAL_TYPE_TO_MAIN_SCENE	2
/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	float width;
	float height; 

public:
	float startX, startY;
	CPortal(float l, float t, float r, float b,float startX, float startY, int model, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }
};