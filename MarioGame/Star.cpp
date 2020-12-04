#include "Star.h"

CStar::CStar()
{
	SetState(STAR_STATE_DISAPPEAR);
}



void CStar::Render()
{
	if (state != STAR_STATE_DISAPPEAR)
	{
		animation_set->at(0)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CStar::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}

void CStar::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STAR_STATE_APPEAR:
		break;
	case STAR_STATE_DISAPPEAR:
		break;
	}
}
