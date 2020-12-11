#pragma once
#include "GameObject.h"
class CHUD : public CGameObject
{
private:
	int typeOfHud;
public:
	CHUD(int type);
	CHUD() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);
};

