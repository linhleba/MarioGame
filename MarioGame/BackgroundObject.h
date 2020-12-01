#pragma once
#include "GameObject.h"


class CBackgroundObject : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
};