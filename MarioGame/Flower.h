#pragma once
#include "GameObject.h"

#define FLOWER_BBOX_WIDTH  16
#define FLOWER_BBOX_HEIGHT 32

class CFlower : public CGameObject
{
private:
	DWORD timeFiring_start;
	bool isFirstFiring = false;
	bool hasFired = false;


	int posFlower = -1;
public:
	CFlower();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void SetHasFired(bool value) { hasFired = value; };

	int GetPositionFlower();
	bool GetHasFired() { return hasFired; }
};