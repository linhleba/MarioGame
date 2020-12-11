#include "HUD.h"

CHUD::CHUD(int type)
{
	typeOfHUD = type;
}

void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CHUD::Render()
{
	int ani = -1;
	switch (typeOfHUD)
	{
	case OBJECT_TYPE_HUD_PANEL:
		ani = HUD_TYPE_PANEL_ANI;
	default:
		break;
	}
	animation_set->at(ani)->Render(x, y);
}

void CHUD::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
}

void CHUD::SetState(int state)
{
}
