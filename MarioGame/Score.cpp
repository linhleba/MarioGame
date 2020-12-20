#include "Score.h"
#include "Game.h"

CScore::CScore()
{
	SetState(SCORE_STATE_DISAPPEAR);
}

void CScore::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = t = r = b;
}

void CScore::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;

	if (levelOfScore > -1)
	{
		if (levelOfScore > 0)
		{
			CGame::GetInstance()->SetScore(levelOfScore * 100);
			SetState(SCORE_STATE_APPEAR);
		}
		else if (levelOfScore == 0)
		{
			SetState(SCORE_LEVEL_STATE_APPEAR);
		}
		levelOfScore = -1;
	}

	if (state == SCORE_STATE_APPEAR || state == SCORE_LEVEL_STATE_APPEAR)
	{
		if (!isMoving)
		{
			isMoving = true;
			isMoving_start = GetTickCount();
		}
		else
		{
			if (GetTickCount() - isMoving_start > TIME_OF_SCORE_DISAPPEARING)
			{
				SetState(SCORE_STATE_DISAPPEAR);
				isMoving = false;
			}
		}
	}

}

void CScore::Render()
{
	if (state != SCORE_STATE_DISAPPEAR)
	{
		int ani = -1;
		if (state == SCORE_LEVEL_STATE_APPEAR)
		{
			ani = SCORE_APPEAR_LEVEL_ANI;
		}
		else
		{
			ani = SCORE_APPEAR_100_ANI;
		}
		if (ani != -1)
		{
			animation_set->at(ani)->Render(x, y);
		}
	}
}

void CScore::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SCORE_STATE_DISAPPEAR:
		vx = 0;
		vy = 0;
		levelOfScore = -1;
		break;
	case SCORE_STATE_APPEAR:
		vy = -0.05;
		break;
	default:
		break;
	}
}

void CScore::SetScore(int value, double x, double y)
{
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();
	if (id == ID_PLAY_SCENE)
	{
		levelOfScore = value;
		this->x = x;
		this->y = y;
	}
}
