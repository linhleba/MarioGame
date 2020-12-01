#pragma once
#include "GameObject.h"
#define COINQUESTION_BBOX_WIDTH  10
#define COINQUESTION_BBOX_HEIGHT 16
class CCoinQuestion : public CGameObject
{
private: 
	DWORD time_Moveup_start = 0;
	DWORD time_Movedown_start = 0;
	bool isUsed = false;
public:
	CCoinQuestion();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);
};