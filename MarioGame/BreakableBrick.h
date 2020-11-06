#pragma once
#include "GameObject.h"

#define BBRICK_BBOX_WIDTH  16
#define BBRICK_BBOX_HEIGHT 16

class CBreakableBrick : public CGameObject
{
public:
	CBreakableBrick();
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};