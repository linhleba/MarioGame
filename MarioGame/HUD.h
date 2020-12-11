#pragma once
#include "GameObject.h"
class CHUD : public CGameObject
{
	int typeOfHUD;
public:
	CHUD(int type);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void SetState(int state);
};

