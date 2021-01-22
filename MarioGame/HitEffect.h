#pragma once
#include "GameObject.h"
class CHitEffect : public CGameObject 
{
private:
	DWORD timeAppear_start;
	bool timeAppear = false;
public:
	CHitEffect();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

