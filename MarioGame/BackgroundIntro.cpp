#include "BackgroundIntro.h"



CBackgroundIntro::CBackgroundIntro(int type)
{
	typeOfBackground = type;
	SetState(BACKGROUND_STATE_DISAPPEAR);
}

void CBackgroundIntro::Render()
{
	if (state != BACKGROUND_STATE_DISAPPEAR)
	{
		animation_set->at(0)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CBackgroundIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (typeOfBackground == OBJECT_TYPE_FIRST_BACKGROUND)
	{
		SetState(BACKGROUND_STATE_APPEAR);
	}
}

void CBackgroundIntro::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}

void CBackgroundIntro::SetState(int state)
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
