#pragma once
#include "GameObject.h"

#define FLOWER_BBOX_WIDTH  10
#define FLOWER_BBOX_HEIGHT 10

class CFlower : public CGameObject
{
private:
	DWORD timeFiring_start;
	bool isFirstFiring = false;
public:
	CFlower();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
};