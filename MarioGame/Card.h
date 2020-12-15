#pragma once
#include "GameObject.h"
#define CARD_BBOX_WIDTH  16
#define CARD_BBOX_HEIGHT 16
class CCard : public CGameObject
{
	DWORD timeStateChanged_start;
	bool isTimeStateChanged = false;

	DWORD isAppearing_start;
	bool isAppearing = false;

public:
	CCard();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

