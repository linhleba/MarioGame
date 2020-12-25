#pragma once
#include "GameObject.h"
#define FRAGMENT_BBOX_WIDTH  0
#define FRAGMENT_BBOX_HEIGHT 0

class CFragments : public CGameObject
{
private:
	bool isUsed = false;
	int typeOfFragment = 0;

	DWORD disappear_start;
	bool isDisappear = false;
public:
	CFragments();
	CFragments(int type);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);

	void SetIsUsed(bool value) { isUsed = value; }

	bool getIsUsed() { return isUsed; }
	int GetTypeOfFragment() { return typeOfFragment; }
};

