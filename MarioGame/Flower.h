#pragma once
#include "GameObject.h"

#define FLOWER_BBOX_WIDTH  10
#define FLOWER_BBOX_HEIGHT 10

class CFlower : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
};