#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "HUD.h"
#include "Card.h"
#include "Score.h"
#include "Grid.h"
#include "Cell.h"
#include "Map.h"

class CPlayScene : public CScene
{
protected:
	Map* map;
	CMario* player;					// A play scene has to have player, right? 
	CScore* score;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> coObjects;
	//Grid* grid;
	Grid* grid;

	vector<CHUD*> staticItems;
	vector<CHUD*> timeCounters;
	vector<CHUD*> scoreCounters;
	vector<CHUD*> moneyCounters;
	vector<CHUD*> stackNormalCounters;
	vector<CHUD*> cardCounters;
	CHUD* lifeCounter;
	CHUD* stackMaxCounter;
	int timeStart = 300;

	vector<int> numPos;

	double camPreX = 0;
	double camPreY = 0;

	DWORD resetTime_start;
	bool isResetTimeStart = false;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_GRID(string line);
	void _ParseSection_MAP(string line);


public:
	CPlayScene(int id, LPCWSTR filePath);

	//bool CompareLayer(const LPGAMEOBJECT &coObjects1, const LPGAMEOBJECT &coObjects2);
	void SortObjectByLayer(vector<LPGAMEOBJECT>* coObjects);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario* GetPlayer() { return player; }
	CScore* GetScore() { return score; }
	//Grid* GetGrid() { return grid; }
	double GetCamPreX() { return camPreX; }
	double GetCamPreY() { return camPreY; }

	bool CheckInViewPortCam(double x, double y)
	{
		CGame* game = CGame::GetInstance();
		return (x > game->GetCamX() && x < (game->GetCamX() + game->GetScreenWidth())
			&& y > game->GetCamY() && y < (game->GetCamY() + game->GetScreenHeight()));
	}
	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

