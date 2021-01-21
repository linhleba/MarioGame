#pragma once
#include "GameObject.h"
#include "define.h"

class CGoomba : public CGameObject
{

	// check dir to set state die reflection
	int dieDir = 0;

	int typeOfGoomba;
	bool isFLying = false;
	DWORD timeFlying_start;

	DWORD start = 0;
	bool isDie = false;
	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void Reset();

public:
	CGoomba(int type);
	virtual void SetState(int state);
	void SetTickCount() { start = GetTickCount(); };
	void SetGoombaDie() { isDie = true; };
	void SetDieDir(double posX) {
		if (posX - this->x >= 0)
		{
			dieDir = -1;
		}
		else
		{
			dieDir = 1;
		}
	}

};