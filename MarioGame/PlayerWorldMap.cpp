#include "PlayerWorldMap.h"
#include "Utils.h"
#include "WorldMapScene.h"

CPlayerWorldMap::CPlayerWorldMap()
{
	SetState(MARIO_STATE_NOT_MOVING);
}

void CPlayerWorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
	
	CWorldMap* worldMap = (CWorldMap*)CGame::GetInstance()->GetCurrentScene();

	if (state == MARIO_STATE_NOT_MOVING)
	{
		preX = this->x;
		preY = this->y;
	}

	else
	{
		isNotMoving = false;
		double deltaX = abs(this->x - preX) - 47;
		double deltaY = abs(this->y - preY) - 47;
		if (abs(this->x - preX) >= 47)
		{
			SetState(MARIO_STATE_NOT_MOVING);
			if (x > preX)
			{
				x -= deltaX;
			}
			else
			{
				x += deltaX;
			}
			worldMap->SetIsKeyDown(false);
			isNotMoving = true;

		}
		if (abs(this->y - preY) >= 47)
		{
			SetState(MARIO_STATE_NOT_MOVING);
			if (y > preY)
			{
				y -= deltaY;
			}
			else
			{
				y += deltaY;
			}
			worldMap->SetIsKeyDown(false);
			isNotMoving = true;
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
		vy = 0.18;
		break;
	case MARIO_STATE_MOVING_LEFT:
		vx = -0.18;
		break;
	case MARIO_STATE_MOVING_UP:
		vy = -0.18;
		break;
	case MARIO_STATE_MOVING_RIGHT:
		vx = 0.18;
		break;
	default:
		break;
	}
}
