#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Map.h"
#include "GameTime.h"
#include "WorldPlayer.h"
#include "Mario.h"
#include "Arrow.h"

#define ANI_THREE_ID 5
#define ANI_BACKGROUND_SECTION_1 2
#define ANI_BACKGROUND_SECTION_2 3
#define ANI_BACKGROUND_SECTION_3 4
#define ANI_GROUND_INTRO 1
#define THREE_POSITION_X 133
#define THREE_POSITION_Y 115
#define GROUND_POSITION_X 128
#define GROUND_POSITION_Y 200
#define SECTION_1 1
#define SECTION_2 2
#define SECTION_3 3
#define BACKGROUND_POSITION_X 128
#define BACKGROUND_POSITION_Y 90
#define BACKGROUND_DOWN_SPEED 3
#define SECTION_2_DURATION 2000

class CIntroScene : public CScene
{
	CArrow* arrow = NULL;
	LPANIMATION three;
	LPANIMATION background[4];
	LPANIMATION ground;
	float point = -300;
	DWORD start_section2 = -1;
	int section = 1;
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	vector<LPGAMEOBJECT> objects;
	CIntroScene(int id, LPCWSTR filePath);
	CArrow* GetArrow() { return arrow; }
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT &o);
};

typedef CIntroScene *LPINTROSCENE;
