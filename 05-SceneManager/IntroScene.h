#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Map.h"
#include "GameTime.h"
#include "WorldPlayer.h"
#include "Mario.h"

#define ANI_THREE_ID 5
class CIntroScene : public CScene
{
	CWorldPlayer* player = NULL;
	LPANIMATION THREE;
	LPANIMATION Background;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	vector<LPGAMEOBJECT> objects;
	CIntroScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT &o);
};

typedef CIntroScene *LPINTROSCENE;
