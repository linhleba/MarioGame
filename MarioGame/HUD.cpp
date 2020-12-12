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
		break;
	case OBJECT_TYPE_HUD_WORLD:
		ani = HUD_TYPE_WORLD_ANI;
		break;
	case OBJECT_TYPE_HUD_MARIO_LUIGI:
		ani = HUD_TYPE_MARIO_LUIGI_ANI;
		break;
	case OBJECT_TYPE_HUD_LIFE:
		ani = HUD_TYPE_NUMBER_ZERO_ANI;
		break;
	case OBJECT_TYPE_HUD_TIME_PICKER:
		ani = HUD_TYPE_NUMBER_ZERO_ANI;
		break;
	case OBJECT_TYPE_HUD_SCORE:
		ani = HUD_TYPE_NUMBER_ZERO_ANI;
		break;
	case OBJECT_TYPE_HUD_MONEY:
		ani = HUD_TYPE_NUMBER_ZERO_ANI;
		break;
	case OBJECT_TYPE_HUD_STACK_NORMAL:
		ani = HUD_TYPE_STACK_NORMAL_EMPTY;
		break;
	case OBJECT_TYPE_HUD_STACK_MAX:
		ani = HUD_TYPE_STACK_MAX_EMPTY;
		break;
	default:
		break;
	}
	if (ani != -1)
	{
		animation_set->at(ani)->Render(x, y);
	}
}

void CHUD::Render(int indexTime)
{
	int ani = indexTime;
	animation_set->at(ani)->Render(x, y);
}

void CHUD::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
}

void CHUD::SetState(int state)
{
}
