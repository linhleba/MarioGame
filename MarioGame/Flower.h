#pragma once
#include "GameObject.h"

#define FLOWER_BBOX_WIDTH  16
#define FLOWER_BBOX_HEIGHT 32

class CFlower : public CGameObject
{
private:
	int typeOfFlower;
	DWORD timeFiring_start;
	bool isFirstFiring = false;
	bool hasFired = false;


	bool isShortDistance = false;  // xet xem vi tri cua hoa voi mario, true -> khoang cach gan, false -> khoang cach xa
	int posFlower = -1;
public:
	CFlower(int type);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void SetHasFired(bool value) { hasFired = value; };
	void SetIsShortDistance();

	int GetPositionFlower();
	bool GetHasFired() { return hasFired; }
	bool GetIsShortDistance() { return isShortDistance; }
};