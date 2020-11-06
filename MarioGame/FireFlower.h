#pragma once
#include "GameObject.h"

#define FIREFLOWER_BBOX_WIDTH  7
#define FIREFLOWER_BBOX_HEIGHT 8

class CFireFlower : public CGameObject
{
private:
	bool isFiring = false;
	DWORD timeFirinng_start;
	bool flagTimeFiring = false;
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetIsFiring(bool value) { isFiring = value; };

	bool GetIsFiring() { return isFiring; }
};