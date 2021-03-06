#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Map.h"
#include "ObjectWorldMap.h"
#include "Node.h"
#include "NodeList.h"
#include "PlayerWorldMap.h"
#include "HUD.h"
class CWorldMap : public CScene
{
protected:
	//CMario* player;					// A play scene has to have player, right? 
	Map* map;
	bool isKeyDown = false;

	vector<LPGAMEOBJECT> objects;
	
	CPlayerWorldMap* mario;

	//vector<CNode*> nodes;
	CNodeList* nodeList = new CNodeList();

	vector<CHUD*> scoreCounters;
	vector<CHUD*> moneyCounters;
	vector<CHUD*> cardCounters;
	CHUD* lifeCounters;


	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);


public:
	CWorldMap(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CPlayerWorldMap* GetPlayer() { return mario; }
	CNodeList* GetNodeList() { return nodeList; }
	bool GetIsKeyDown() { return isKeyDown; }
	void SetIsKeyDown(bool value) { isKeyDown = value; }

	//friend class CPlayScenceKeyHandler;
};

class CWorldMapScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	CWorldMapScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};


