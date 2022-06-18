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
#define ANI_GROUND_INTRO 5

class CIntroScene : public CScene
{
	CArrow* arrow = NULL;
	LPANIMATION three;
	LPANIMATION background;
	LPANIMATION ground;

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
