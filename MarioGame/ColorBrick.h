#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CColorBrick : public CGameObject
{
public:
	CColorBrick();
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
};