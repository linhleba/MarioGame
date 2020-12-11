#pragma once
#include "GameObject.h"
class CPlayerWorldMap : public CGameObject
{
private:
	//bool isNotMoving = false;
	DWORD isMoving_start = 0;
	//bool isMoving = false;
	bool isNotMoving = true;


	double preX;
	double preY;
public:
	CPlayerWorldMap();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void SetState(int state);
	bool GetIsNotMoving() { return isNotMoving; }
};

