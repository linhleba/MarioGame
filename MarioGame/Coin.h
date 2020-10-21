#pragma once
#include "GameObject.h"
#define BRICK_BBOX_WIDTH  10
#define BRICK_BBOX_HEIGHT 16
class CCoin : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};