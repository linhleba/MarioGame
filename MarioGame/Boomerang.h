#pragma once
#include "GameObject.h"

#define BOOMERANG_BBOX_WIDTH	16
#define BOOMERANG_BBOX_HEIGHT	16
class CBoomerang : public CGameObject
{
private:
	// check if boomerang is using or not
	bool isUsing = false;
	int typeOfBoomerang;

	// change state by time
	DWORD isChangeState_start;
	bool  isChangeStart = false;

	// check the collision with Boomerang Man
	bool isAllowForCollision = false;

	// Check previous time 
	DWORD preTime_start = 0;
	DWORD diff_time = 0;

public:
	CBoomerang();
	CBoomerang(int type);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void SetIsUsing(bool value) { isUsing = value; }
	bool GetIsUsing() { return isUsing; }
	void SetTimeForBoomerang() { isChangeStart = true; isChangeState_start = GetTickCount(); }

	int GetTypeOfBoomerang() { return typeOfBoomerang; }
};

