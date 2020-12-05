#pragma once
#include "GameObject.h"

#define STAR_BBOX_WIDTH 16
#define STAR_BBOX_HEIGHT 16

class CStar : public CGameObject
{
public:
	CStar();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);
};
