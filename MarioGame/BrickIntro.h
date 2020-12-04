#pragma once
#include "GameObject.h"

#define BRICK_INTRO_BBOX_WIDTH  256
#define BRICK_INTRO_BBOX_HEIGHT 38

class CBrickIntro : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
};