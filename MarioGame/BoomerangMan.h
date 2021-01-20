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

	// Check time for rendering ani
	DWORD timeRenderingThrowing_start;
	//bool checkTimeRenderingThrowing = false;


	// Check previous time 
	DWORD preTime_start = 0;
	DWORD diff_time = 0;
public:
	CBoomerangMan();
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void SetTimeRenderThrowing() {
		if (timeRenderingThrowing_start == 0)
			timeRenderingThrowing_start = GetTickCount();
	}
};

