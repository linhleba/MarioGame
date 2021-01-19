#pragma once
#include "GameObject.h"
#define BOOMERANG_MAN_BBOX_WIDTH	16
#define BOOMERANG_MAN_BBOX_HEIGHT	24
class CBoomerangMan : public CGameObject
{
	DWORD isChangeState_start = 0;
	bool isChangeState = false;

	// Check the state for throwing boomerang
	bool checkThrowingBoomerang = false;
public:
	CBoomerangMan();
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

