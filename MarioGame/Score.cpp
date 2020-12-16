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

	if (levelOfScore != 0)
	{
		SetState(SCORE_STATE_APPEAR);
		CGame::GetInstance()->SetScore(levelOfScore*100);
		levelOfScore = 0;
	}

	if (state == SCORE_STATE_APPEAR)
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
		animation_set->at(SCORE_APPEAR_ANI)->Render(x, y);
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
		levelOfScore = 0;
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
	levelOfScore = value;
	this->x = x;
	this->y = y;
}
