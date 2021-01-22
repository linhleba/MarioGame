#pragma once
#include "GameObject.h"
#define TAIL_BBOX_WIDTH  4
#define TAIL_BBOX_HEIGHT 1
class CTail : public CGameObject
{
private:
	bool isHitEffect = false;
	bool isTailing = false;
	DWORD timeTailing_start;
public:
	CTail();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);
};