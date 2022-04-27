#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Map.h"
#include "GameTime.h"
#include "WorldPlayer.h"
#include "Mario.h"

#define ADJUST_PADDING 10

class CWorldScene : public CScene
{
	CWorldPlayer* player = NULL;
	CMario* mario = NULL;
	GameTime* gameTime = new GameTime();
	int gameTimeRemain = 0;
	bool isTurnOnCamY = false;
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	Map* map = NULL;
	vector<LPGAMEOBJECT> objects;
	CWorldScene(int id, LPCWSTR filePath);
	CWorldPlayer* GetPlayer() { return player; }
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void Clear();
	void PurgeDeletedObjects();
	void LoadBackup();
	void BackUpPlayer();
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CWorldScene* LPWORLDSCENE;

