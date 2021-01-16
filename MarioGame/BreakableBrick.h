#pragma once
#include "GameObject.h"

#define BBRICK_BBOX_WIDTH  16
#define BBRICK_BBOX_HEIGHT 16

class CBreakableBrick : public CGameObject
{
private:
	int countFragment = 0;
	bool hasUsed = false;
	bool isCoin = false;
public:
	CBreakableBrick();
	virtual void Render();
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
};