#pragma once
#include "GameObject.h"

#define PIPE_BBOX_WIDTH  16
#define PIPE_BBOX_HEIGHT 16

class CPipe : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};