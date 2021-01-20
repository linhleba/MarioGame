#pragma once
#include "GameObject.h"
#define COIN_BBOX_WIDTH  10
#define COIN_BBOX_HEIGHT 16
class CCoin : public CGameObject
{

public:
	CCoin();
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);
};