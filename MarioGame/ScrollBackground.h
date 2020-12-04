#pragma once
#include "GameObject.h"
#include "algorithm"
#include "Mario.h"
#include "IntroScene.h"
class CScrollBackground : public CGameObject
{
private:
	DWORD time_ScrollStart;
	bool isScrollStart = false;
public:
	CScrollBackground();
	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

