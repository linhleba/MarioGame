#include "BreakableBrick.h"

CBreakableBrick::CBreakableBrick()
{
	SetState(BREAKBRICK_STATE_APPEAR);
}

void CBreakableBrick::Render()
{
	if (state == BREAKBRICK_STATE_APPEAR)
	{
		animation_set->at(0)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CBreakableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == BREAKBRICK_STATE_APPEAR)
	{
		l = x;
		t = y;
		r = x + BBRICK_BBOX_WIDTH;
		b = y + BBRICK_BBOX_HEIGHT;
	}
	else
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}

void CBreakableBrick::SetState(int state)
{
	CGameObject::SetState(state);
}