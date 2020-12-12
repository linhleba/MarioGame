#pragma once
#include "GameObject.h"
#include "Game.h"
class CHUD : public CGameObject
{
	int typeOfHUD;
	vector<int> scoreCounters;
	int scoreCounter;
public:
	CHUD(int type);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Render(int indexTime);
	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void SetState(int state);
};

