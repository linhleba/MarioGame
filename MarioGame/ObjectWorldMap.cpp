#include "ObjectWorldMap.h"
#include "Utils.h"

CObjectWorldMap::CObjectWorldMap(int type)
{
	typeOfObject = type;
}

void CObjectWorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CObjectWorldMap::Render()
{
	int ani = -1;
	switch (typeOfObject)
	{
	case OBJECT_TYPE_MARIO:
		//DebugOut(L"hello world \n");
		ani = MARIO_WORLDMAP_ANI_APPEAR;
		break;
	case OBJECT_TYPE_HELP:
		ani = HELP_ANI_APPEAR;
		break;
	case OBJECT_TYPE_GOLD_DIGGER:
		ani = GOLD_DIGGER_ANI_WALKING_RIGHT;
		break;
	case OBJECT_TYPE_BUSH:
		ani = BUSH_ANI_APPEAR;
		break;
	}
	animation_set->at(ani)->Render(x, y);
}

void CObjectWorldMap::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
	left = top = right = bottom = 0;
}

void CObjectWorldMap::SetState(int state)
{
	CGameObject::SetState(state);
}
