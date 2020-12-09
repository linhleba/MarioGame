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
	if (state != MARIO_STATE_NOT_MOVING)
	{
		if (!isMoving)
		{
			isMoving_start = GetTickCount();
			isMoving = true;
		}
		else
		{
			if (GetTickCount() - isMoving_start >= 220)
			{
				SetState(MARIO_STATE_NOT_MOVING);
				isMoving = false;
				worldMap->SetIsKeyDown(false);
			}
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
