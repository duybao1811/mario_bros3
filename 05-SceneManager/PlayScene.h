#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Map.h"
#include "GameTime.h"
class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	CMario* player = NULL;					
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
	vector<LPGAMEOBJECT> ListEffect;

	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void SetCam(float cx, float cy);
	CMario* GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	void LoadBackup();
	void BackUpPlayer();
	void PutPlayer(CMario* m)
	{
		if (dynamic_cast<CMario*>(objects[0]))
			objects[0] = m;
	}
	void SetPlayer(CMario* mario) { player = mario; }
	GameTime* GetGameTime() {
		return gameTime;
	}
	void SetGameTime(GameTime* _gameTime) {
		gameTime = _gameTime;
	}
};

typedef CPlayScene* LPPLAYSCENE;

