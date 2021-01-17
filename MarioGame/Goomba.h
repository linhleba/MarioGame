#pragma once
#include "GameObject.h"
#include "define.h"

class CGoomba : public CGameObject
{
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
};