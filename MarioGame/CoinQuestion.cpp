#include "CoinQuestion.h"
#include "Question.h"
#include "Mario.h"
#include "Game.h"
#include "PlayScence.h"

CCoinQuestion::CCoinQuestion()
{
	SetState(COIN_STATE_DISAPPEAR);
}

void CCoinQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CScore* score = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetScore();
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
			if (question->GetTypeOfQuestion() != OBJECT_TYPE_SPECIAL_COIN_BRICK)
			{
				if (!isUsed && question->GetState() == QUESTION_STATE_BLANK && this->x == question->x)
				{
					SetState(COIN_STATE_MOVING_UP);
					isUsed = true;
				}
			}
			else
			{
				if (!isUsed && question->GetState() == QUESTION_STATE_MOVEMENT && this->x == question->x)
				{
					if (!isSetCoinPos)
					{
						this->SetPosition(originX, originY);
						isSetCoinPos = true;
					}
					SetState(COIN_STATE_MOVING_UP);
				}
				else if (!isUsed && question->GetState() == QUESTION_STATE_BLANK && this->x == question->x)
				{
					SetState(COIN_STATE_MOVING_UP);
					isUsed = true;
				}
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
			time_Moveup_start = 0;
		}
	}

	else if (state == COIN_STATE_MOVING_DOWN)
	{
		if (time_Movedown_start == 0)
		{
			time_Movedown_start = GetTickCount();
		}
		else if (GetTickCount() - time_Movedown_start > 160)
		{
			score->SetScore(1, x, y);
			SetState(COIN_STATE_DISAPPEAR);
			time_Movedown_start = 0;
			isSetCoinPos = false;
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
		vy = 0;
		break;
	case COIN_STATE_MOVING_UP:
		vy = -0.2;
		break;
	case COIN_STATE_MOVING_DOWN:
		vy = 0.2;
		break;
	}
}