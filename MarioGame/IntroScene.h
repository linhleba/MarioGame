#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "BackgroundIntro.h"
#include "Number.h"
#include "Item.h"
#include "Star.h"
#include "BackgroundObject.h"
#include "MenuIntro.h"

class CIntroScene : public CScene
{
protected:
	CMario* player;					// A play scene has to have player, right? 

	CMario* greenMario;
	CMario* redMario;

	vector<CBackgroundIntro*> firstBackground;
	CBackgroundIntro* secondBackground;
	CBackgroundIntro* finalBackground;
	CNumber* number;
	CGoomba* goomba;
	vector<CItem*> item;
	CKoopas* greenKoopas;
	CKoopas* blackKoopas;
	CStar* star;
	vector<CBackgroundObject*> cBush;
	CMenuIntro* menuIntro;

	vector<LPGAMEOBJECT> objects;

	bool firstTime_start = false;
	bool secondTime_start = false;

	DWORD time_start;
	bool isTimeStart = false;
	DWORD timeRedSitDown_start;
	bool isTimeRedSitDown = false;

	// Mario stand up when sit down
	bool isRedStandUp = false;
	int countJumpGreen = 0;
	// check if set final background state;
	bool isSetFinalBackground = false;

	// check time when Mario appear be hitted state
	DWORD timeHitted_start;
	bool isTimeHitted = false;
	// Check time when Mario look ahead state
	DWORD timeLookAhead_start;

	// check time fall 
	DWORD checkFall_start;
	bool firstTimeGoombaWalking = false;
	bool firstGoombadie = false;

	// check time mario tail idle
	bool checkFirstTimeTail = false;
	bool firstTimeToShoot = false;
	DWORD checkIdle_start;
	bool checkIdleStart = false;
	//bool checkIsHolding = false;

	// check time mario walking when shoots
	DWORD checkWalking_start;
	bool checkWalkingStart = false;

	// count time for Koopas
	int countTimeRunning = 0;
	DWORD firstTimeRunning_start;
	DWORD firstTimeGreenHold_start;
	DWORD firstTimeToRedRunning_start;

	// count time RedMario hold Koopas
	DWORD firstTimeRedHoldKoopas;
	DWORD firstTimeRedShooting;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);


public:
	CIntroScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario* GetPlayer() { return player; }
	CMario* GetRedMario() { return redMario; }
	CMario* GetGreenMario() { return greenMario; }
	CMenuIntro* GetMenuIntro() { return menuIntro; }

	//friend class CPlayScenceKeyHandler;
};

class CIntroSceneKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CIntroSceneKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};


