#pragma once
#include "GameObject.h"
class CObjectWorldMap : public CGameObject
{
	int typeOfObject;
public:
	CObjectWorldMap(int type);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void SetState(int state);
};

