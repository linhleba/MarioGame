#pragma once
#include "GameObject.h"
#define BBOX_MOVING_BRICK_WIDTH 48
#define BBOX_MOVING_BRICK_HEIGHT 16
class CMovingBrick : public CGameObject
{
public:
	CMovingBrick();
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

