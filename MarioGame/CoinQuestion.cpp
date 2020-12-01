#include "CoinQuestion.h"
#include "Question.h"

CCoinQuestion::CCoinQuestion()
{
	SetState(COIN_STATE_DISAPPEAR);
}

void CCoinQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (state != COIN_STATE_DISAPPEAR)
	{
		x += dx;
		y += dy;
	}

	for (size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CQuestion*>(obj))
		{
			CQuestion* question = dynamic_cast<CQuestion*>(obj);
			if (!isUsed && question->GetState() == QUESTION_STATE_BLANK && this->x == question->x)
			{
				SetState(COIN_STATE_MOVING_UP);
				isUsed = true;
			}
		}
	}

	if (state == COIN_STATE_MOVING_UP)
	{
		if (time_Moveup_start == 0)
		{
			time_Moveup_start = GetTickCount();
		}

		else if (GetTickCount() - time_Moveup_start > 200)
		{
			SetState(COIN_STATE_MOVING_DOWN);
		}
	}

	else if (state == COIN_STATE_MOVING_DOWN)
	{
		if (time_Movedown_start == 0)
		{
			time_Movedown_start = GetTickCount();
		}
		else if (GetTickCount() - time_Movedown_start > 200)
		{
			SetState(COIN_STATE_DISAPPEAR);
		}
	}
}

void CCoinQuestion::Render()
{
	if (state != COIN_STATE_DISAPPEAR)
	{
		animation_set->at(0)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CCoinQuestion::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	if (state != COIN_STATE_DISAPPEAR)
	{
		l = x;
		t = y;
		r = x + COINQUESTION_BBOX_WIDTH;
		b = y + COINQUESTION_BBOX_HEIGHT;
	}
	else
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}

void CCoinQuestion::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_STATE_DISAPPEAR:
		/*	y = 0;
			x = 0;*/
		break;
	case COIN_STATE_MOVING_UP:
		vy = -0.2;
		break;
	case COIN_STATE_MOVING_DOWN:
		vy = 0.2;
		break;
	}
}