#pragma once
#include "GameObject.h"
class CMenuIntro : public CGameObject
{
public:
	CMenuIntro();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);

};

