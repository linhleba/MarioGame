#pragma once
#include "GameObject.h"


class CBackgroundObject : public CGameObject
{
	int typeOfBackground;
	bool isRender = false;
public:
	CBackgroundObject() {};
	CBackgroundObject(int type);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	void SetIsRender(bool value) { isRender = value; }
};