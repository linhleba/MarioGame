#pragma once
#include "GameObject.h"


class CNumber : public CGameObject
{
	// first time to get appear state
	bool firstTimeToAppear = false;

	DWORD timeChangeState_start;
	bool  isChangeState = false;
public:
	CNumber();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);
};
