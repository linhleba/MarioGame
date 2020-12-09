#pragma once
#include "GameObject.h"
class CPlayerWorldMap : public CGameObject
{
private:
	//bool isNotMoving = false;
	DWORD isMoving_start;
	bool isMoving = false;

	double preX;
	double preY;
public:
	CPlayerWorldMap();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void SetState(int state);
};

