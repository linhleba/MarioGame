#pragma once
#include "GameObject.h"

#define PLETTER_BBOX_WIDTH  16
#define PLETTER_BBOX_HEIGHT 16

class CPLetter : public CGameObject
{
public:
	CPLetter();
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
};