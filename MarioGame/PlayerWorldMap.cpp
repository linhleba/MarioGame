#include "PlayerWorldMap.h"
#include "Utils.h"

CPlayerWorldMap::CPlayerWorldMap()
{
	SetState(MARIO_STATE_NOT_MOVING);
}

void CPlayerWorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (state == MARIO_STATE_NOT_MOVING)
	{
		preX = this->x;
		preY = this->y;
	}

	else
	{
		if (abs(this->x - preX) >= 47 || abs(this->y - preY) >= 47)
		{
			SetState(MARIO_STATE_NOT_MOVING);
		}
	}
}

void CPlayerWorldMap::Render()
{
	animation_set->at(MARIO_WORLDMAP_ANI_APPEAR)->Render(x, y);
}

void CPlayerWorldMap::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
	left = top = right = bottom = 0;
}

void CPlayerWorldMap::SetState(int state)
{
	CGameObject::SetState(state);
	switch(state)
	{
	case MARIO_STATE_NOT_MOVING:
		vx = 0;
		vy = 0;
		break;
	case MARIO_STATE_MOVING_DOWN:
		vy = 0.05f;
		break;
	case MARIO_STATE_MOVING_LEFT:
		vx = -0.05f;
		break;
	case MARIO_STATE_MOVING_UP:
		vy = -0.05f;
		break;
	case MARIO_STATE_MOVING_RIGHT:
		vx = 0.05f;
		break;
	default:
		break;
	}
}
