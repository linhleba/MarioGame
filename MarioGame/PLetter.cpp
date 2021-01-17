#include "PLetter.h"
#include "Coin.h"
#include "Collision.h"
#include "Mario.h"
#include "BreakableBrick.h"

CPLetter::CPLetter()
{
	SetState(PLETTER_STATE_DISAPPEAR);
}


void CPLetter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	if (state != PLETTER_STATE_DISAPPEAR)
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);

	
	// check state PLetter if state is small appear, all of breakablebrick will change coins
	if (state == PLETTER_STATE_SMALL_APPEAR && !isUsed)
	{
		for (size_t i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CBreakableBrick*>(obj))
			{
				CBreakableBrick* breakableBrick = dynamic_cast<CBreakableBrick*>(obj);
				if (breakableBrick->GetState() == BREAKBRICK_STATE_APPEAR)
				{
					breakableBrick->SetState(BREAKBRICK_STATE_COIN);
				}
			}
		}
		isUsed = true;
	}

	if (coEvents.size() != 0)
	{
		double min_tx, min_ty, nx = 0, ny;
		double rdx = 0;
		double rdy = 0;
		collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CMario*>(e->obj))
			{ 
				CMario* mario = dynamic_cast<CMario*>(e->obj);
				if (ny != 0 && nx == 0 && state != PLETTER_STATE_SMALL_APPEAR)
				{
					SetState(PLETTER_STATE_SMALL_APPEAR);
					SetPosition(x, this->y + 10);
				}
			}
		}

	}


}

void CPLetter::Render()
{
	if (state == PLETTER_STATE_APPEAR)
	{
		animation_set->at(PLETTER_ANI_APPEAR)->Render(x, y);
	}
	else if (state == PLETTER_STATE_SMALL_APPEAR)
	{
		animation_set->at(PLETTER_ANI_SMALL_APPEAR)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CPLetter::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLETTER_STATE_APPEAR:
		y -= 16;
		break;
	}
}

void CPLetter::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	if (state != PLETTER_STATE_DISAPPEAR)
	{
		l = x;
		t = y;
		r = x + PLETTER_BBOX_WIDTH;
		b = y + PLETTER_BBOX_HEIGHT;
	}
	else
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}