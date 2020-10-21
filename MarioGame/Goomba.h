#pragma once
#include "GameObject.h"
#include "define.h"

class CGoomba : public CGameObject
{
	DWORD start = 0;
	bool isDie = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CGoomba();
	virtual void SetState(int state);
	void SetTickCount() { start = GetTickCount(); };
	void SetGoombaDie() { isDie = true; };
};