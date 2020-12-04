#pragma once
#include "GameObject.h"


class CBackgroundIntro : public CGameObject
{
private: 
	int typeOfBackground;
public:
	CBackgroundIntro(int type);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);

	int GetTypeOfBackground() { return typeOfBackground; }
};
