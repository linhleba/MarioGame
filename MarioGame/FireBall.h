#pragma once
#include "GameObject.h"

#define FIREBALL_BBOX_WIDTH  7
#define FIREBALL_BBOX_HEIGHT 8

class CFireBall : public CGameObject
{
private:
	// Limit the position of the fire ball
	double topBoundary;
	bool isFiring = false;
	DWORD timeFirinng_start; 
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	void SetTopBoundary(double value) { topBoundary = value; };
	void SetIsFiring(bool value) { isFiring = value; };
	void SetTimeFiringStart() { timeFirinng_start = GetTickCount(); };
	
	bool CheckTimeExistFiring() { return GetTickCount() - timeFirinng_start < 3000; }  
	bool GetIsFiring(){return isFiring; }
};