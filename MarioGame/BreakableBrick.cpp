#include "BreakableBrick.h"
#include "PLetter.h"
#include "Collision.h"
#include "Mario.h"
#include "Game.h"
#include "Fragments.h"

CBreakableBrick::CBreakableBrick()
{
	SetState(BREAKBRICK_STATE_APPEAR);
	this->layerRender = 3;
}
void CBreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state == BREAKBRICK_STATE_MOVING_UP)
	{
		if (isMovingUp)
		{
			if (countTimeMoving > 4)
			{
				isMovingUp = false;
			}
			else
			{
				y -= 1;
				countTimeMoving++;
			}
		}
		
		else
		{
			if (countTimeMoving != 0)
			{
				y += 1;
				countTimeMoving--;
			}
			if (countTimeMoving == 0)
			{
				isMovingUp = true;
				SetState(BREAKBRICK_STATE_APPEAR);
			}
		}
	}
	if (state == BREAKBRICK_STATE_DISAPPEAR)
	{
		for (size_t i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CPLetter*>(obj))
			{
				CPLetter* p = dynamic_cast<CPLetter*>(obj);
				if (p->x == this->x && p->y == this->y)
				{
					p->SetState(PLETTER_STATE_APPEAR);
					SetState(BREAKBRICK_STATE_BLANK_QUESTION);
				}
			}
			if (!hasUsed && isCoin == false)
			{ 
				if (dynamic_cast<CFragments*>(obj))
				{
					CFragments* fragment = dynamic_cast<CFragments*>(obj);
					if (fragment->getIsUsed() == false)
					{
						fragment->SetIsUsed(true);
						fragment->SetState(FRAGMENT_STATE_APPEAR);
						switch (fragment->GetTypeOfFragment())
						{
						case OBJECT_TYPE_FRAGMENT_LEFTTOP:
							fragment->SetPosition(this->x, this->y);
							break;
						case OBJECT_TYPE_FRAGMENT_RIGHTTOP:
							fragment->SetPosition(this->x + 16, this->y);
							break;
						case OBJECT_TYPE_FRAGMENT_LEFTBOTTOM:
							fragment->SetPosition(this->x, this->y + 16);
							break;
						case OBJECT_TYPE_FRAGMENT_RIGHTBOTTOM:
							fragment->SetPosition(this->x + 16, this->y + 16);
							break;
						}
					}
					countFragment++;
					if (countFragment > 4)
					{
						hasUsed = true;
					}
				}
			}
		}
	}
	if (state == BREAKBRICK_STATE_COIN)
	{
		if (timeCoin_start == 0)
		{
			timeCoin_start = GetTickCount();
		}
		else
		{
			if (GetTickCount() - timeCoin_start > TIME_BREAKBRICK_STATE_COIN_CHANGE)
			{
				SetState(BREAKBRICK_STATE_APPEAR);
				timeCoin_start = 0;
			}
		}
	}

	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (state != BREAKBRICK_STATE_DISAPPEAR)
	{
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	}
	if (coEvents.size() != 0)
	{
		double min_tx, min_ty, nx = 0, ny;
		double rdx = 0;
		double rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CMario*>(e->obj) && state == BREAKBRICK_STATE_COIN)
			{
				CGame::GetInstance()->SetMoney();
				SetState(BREAKBRICK_STATE_DISAPPEAR);
			}
		}
	}

}
void CBreakableBrick::Render()
{
	if (state == BREAKBRICK_STATE_APPEAR || state == BREAKBRICK_STATE_MOVING_UP)
	{
		animation_set->at(BREAKBRICK_ANI_APPEAR)->Render(x, y);
	}
	else if (state == BREAKBRICK_STATE_BLANK_QUESTION)
	{
		animation_set->at(BREAKBRICK_ANI_BLANKQUESTION)->Render(x, y);
	}
	else if (state == BREAKBRICK_STATE_COIN)
	{
		animation_set->at(BREAKBRICK_ANI_COIN)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CBreakableBrick::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	if (state != BREAKBRICK_STATE_DISAPPEAR)
	{
		l = x;
		t = y;
		r = x + BBRICK_BBOX_WIDTH;
		b = y + BBRICK_BBOX_HEIGHT;
	}
	else
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}

void CBreakableBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BREAKBRICK_STATE_COIN:
		isCoin = true;
		break;
	case BREAKBRICK_STATE_APPEAR:
		isCoin = false;
		break;
	}
}