#include "Boomerang.h"

CBoomerang::CBoomerang()
{
	SetState(BOOMERANG_STATE_IDLE);
}

void CBoomerang::Render()
{
}

void CBoomerang::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = x;
	t = y;
	r = x + BOOMERANG_BBOX_WIDTH;
	b = y + BOOMERANG_BBOX_HEIGHT;
}

void CBoomerang::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOOMERANG_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case BOOMERANG_STATE_FLYING_TOP:
		break;
	case BOOMERANG_STATE_FLYING_RIGHT:
		break;
	case BOOMERANG_STATE_FLYING_BOTTOM:
		break;
	case BOOMERANG_STATE_FLYING_LEFT:
		break;
	default:
		break;
	}
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state == BOOMERANG_STATE_FLYING_TOP)
	{

	}
}
