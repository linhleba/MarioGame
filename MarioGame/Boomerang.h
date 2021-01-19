#pragma once
#include "GameObject.h"

#define BOOMERANG_BBOX_WIDTH	16
#define BOOMERANG_BBOX_HEIGHT	16
class CBoomerang : public CGameObject
{
private:
	// check if boomerang is using or not
	bool isUsing = false;

public:
	CBoomerang();
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void SetIsUsing(bool value) { isUsing = value; }
	bool GetIsUsing() { return isUsing; }
};

