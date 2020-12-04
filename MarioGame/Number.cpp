#include "Number.h"

CNumber::CNumber()
{
	SetState(NUMBER_THREE_STATE_DISAPPEAR);
}



void CNumber::Render()
{
	if (state != NUMBER_THREE_STATE_DISAPPEAR)
	{
		animation_set->at(0)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CNumber::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CNumber::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}

void CNumber::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BACKGROUND_STATE_APPEAR:
		break;
	case BACKGROUND_STATE_DISAPPEAR:
		break;
	}
}
