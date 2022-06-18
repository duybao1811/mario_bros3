#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Utils.h"

#define ANI_THREE_ID 5

class CIntroScene : public CScene
{
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);

	void LoadAssets(LPCWSTR assetFile);
	LPANIMATION THREE;
public:
	vector<LPGAMEOBJECT> objects;
	CIntroScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void Clear();
	void PurgeDeletedObjects();
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CIntroScene* LPINTROSCENE;

