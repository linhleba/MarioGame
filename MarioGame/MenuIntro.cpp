#include "MenuIntro.h"

CMenuIntro::CMenuIntro()
{
	SetState(MENU_INTRO_STATE_DISAPPEAR);
}

void CMenuIntro::Render()
{
	int ani = -1;
	if (state != MENU_INTRO_STATE_DISAPPEAR)
	{
		if (state == MENU_INTRO_STATE_PLAYER1)
		{
			ani = MENU_INTRO_ANI_PLAYER1;
		}
		else if (state == MENU_INTRO_STATE_PLAYER2)
		{
			ani = MENU_INTRO_ANI_PLAYER2;
		}
		animation_set->at(ani)->Render(x, y);
	}
}

void CMenuIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CMenuIntro::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = t = r = b = 0;
}

void CMenuIntro::SetState(int state)
{
	CGameObject::SetState(state);
}
