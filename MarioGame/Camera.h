#pragma once
#include "GameObject.h"
class CCamera : public CGameObject
{
private:
	double posX2;
	double posY2;
	double conY;
	double minX;
	double maxX;

	// false: camera has vx, true: based on Mario Pos
	bool basedOnPlayer;
public:
	CCamera();
	CCamera(double x2, double y2, double conY, bool value, double minX, double maxX);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void Update(DWORD dt);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	double GetPosX2() { return posX2; }
	double GetPosY2() { return posY2; }
	double GetCondtionY() { return conY; }
	bool GetBasedOnPlayer() { return basedOnPlayer; }
};

