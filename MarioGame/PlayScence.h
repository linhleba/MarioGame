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

class CPlayScene : public CScene
{
protected:
	CMario* player;					// A play scene has to have player, right? 
	CScore* score;
	vector<LPGAMEOBJECT> objects;

	vector<CHUD*> staticItems;
	vector<CHUD*> timeCounters;
	vector<CHUD*> scoreCounters;
	vector<CHUD*> moneyCounters;
	vector<CHUD*> stackNormalCounters;
	vector<CHUD*> cardCounters;
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


public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario* GetPlayer() { return player; }
	CScore* GetScore() { return score; }
	double GetCamPreX() { return camPreX; }
	double GetCamPreY() { return camPreY; }

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

