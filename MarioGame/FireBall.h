#pragma once
#include "GameObject.h"

#define FIREBALL_BBOX_WIDTH  7
#define FIREBALL_BBOX_HEIGHT 8

class CFireBall : public CGameObject
{
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};