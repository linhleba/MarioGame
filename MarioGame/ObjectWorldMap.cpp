#include "ObjectWorldMap.h"
#include "Utils.h"

CObjectWorldMap::CObjectWorldMap(int type)
{
	typeOfObject = type;
	SetState(OBJECT_STATE_APPEAR);
}

void CObjectWorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
	switch (typeOfObject)
	{
	case OBJECT_TYPE_HELP:
		if (!checkIsHelpStart)
		{
			if (GetTickCount() - isHelp_start > 1000)
			{
				isHelp_start = GetTickCount();
				checkIsHelpStart = true;
				SetState(OBJECT_STATE_APPEAR);
			}
		}
		else
		{
			if (GetTickCount() - isHelp_start > 1000)
			{
				SetState(OBJECT_STATE_DISAPPEAR);
				checkIsHelpStart = false;
				isHelp_start = GetTickCount();
			}
		}
		break;
	case OBJECT_TYPE_GOLD_DIGGER:
		if (!checkIsDiggerStart)
		{
			if (GetTickCount() - isDigger_start > 1000)
			{
				isDigger_start = GetTickCount();
				checkIsDiggerStart = true;
				SetState(GOLD_DIGGER_STATE_WALKING_RIGHT);
			}
		}
		else
		{
			if (GetTickCount() - isDigger_start > 1000)
			{
				SetState(GOLD_DIGGER_STATE_WALKING_LEFT);
				checkIsDiggerStart = false;
				isDigger_start = GetTickCount();
			}
		}
	default:
		break;
	}
}

void CObjectWorldMap::Render()
{
	int ani = -1;
	switch (typeOfObject)
	{
	case OBJECT_TYPE_HELP:
		ani = HELP_ANI_APPEAR;
		break;
	case OBJECT_TYPE_GOLD_DIGGER:
		if (state == GOLD_DIGGER_STATE_WALKING_RIGHT)
		{
			ani = GOLD_DIGGER_ANI_WALKING_RIGHT;
		}
		else if (state == GOLD_DIGGER_STATE_WALKING_LEFT)
		{
			ani = GOLD_DIGGER_ANI_WALKING_LEFT;
		}
		break;
	case OBJECT_TYPE_BUSH:
		ani = BUSH_ANI_APPEAR;
		break;
	}
	if (state != OBJECT_STATE_DISAPPEAR)
	{
		animation_set->at(ani)->Render(x, y);
	}
}

void CObjectWorldMap::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
	left = top = right = bottom = 0;
}

void CObjectWorldMap::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOLD_DIGGER_STATE_WALKING_RIGHT:
		vx = 0.02f;
		break;
	case GOLD_DIGGER_STATE_WALKING_LEFT:
		vx = -0.02f;
		break;
	}
}
