#include "FireFlower.h"
#include "Collision.h"
#include "Mario.h"
#include "Flower.h"
#include "Koopas.h"

CFireFlower::CFireFlower()
{
	this->layerRender = INDEX_LAYER_RENDER_FIREFLOWER;
}

void CFireFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (state != FIRE_FLOWER_STATE_DISAPPEAR)
	{
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		double min_tx, min_ty, nx = 0, ny;
		double rdx = 0;
		double rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (!dynamic_cast<CMario*>(e->obj))
			{
				nx = 0;
				ny = 0;
				e->nx = 0;
				e->ny = 0;
			}
		}
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

	}
	for (size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CFlower*>(obj))
		{
			CFlower* flower = dynamic_cast<CFlower*>(obj);

			// Set isFiring before setting hasFired for flower
			if (isFiring == false)
			{
				if (flower->GetState() == FLOWER_STATE_IDLE && !flower->GetHasFired())
				{
					flower->SetHasFired(true);
					isFiring = true;
					SetPosition(flower->x, flower->y);
					nx = flower->nx;
					ny = flower->ny;
				}
			}
		}
	}
	if (isFiring == true)
	{
		for (size_t i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CFlower*>(obj))
			{
				CFlower* flower = dynamic_cast<CFlower*>(obj);
				if (flower->GetIsShortDistance() == false)
				{
					SetState(FIRE_FLOWER_STATE_APPEAR_LONG_DISTANCE);
				}
				else
				{
					SetState(FIRE_FLOWER_STATE_APPEAR_SHORT_DISTANCE);
				}
			}
		}
		if (flagTimeFiring == false)
		{
			timeFirinng_start = GetTickCount();
			flagTimeFiring = true;
		}
		else
		{
			if (GetTickCount() - timeFirinng_start > TIME_FIRING_FIRE_FLOWER_START)
			{
				SetState(FIRE_FLOWER_STATE_DISAPPEAR);
				flagTimeFiring = false;
				isFiring = false;
			}
		}
	}
	else
	{
		SetState(FIRE_FLOWER_STATE_DISAPPEAR);
	}
}
void CFireFlower::Render()
{
	if (state != FIRE_FLOWER_STATE_DISAPPEAR)
	{
		animation_set->at(0)->Render(x, y);
	}
}

void CFireFlower::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	if (state != FIRE_FLOWER_STATE_DISAPPEAR)
	{
		l = x;
		t = y;
		r = x + FIREFLOWER_BBOX_WIDTH;
		b = y + FIREFLOWER_BBOX_HEIGHT;
	}
	else
	{
		l = t = r = b = 0;
	}
}

void CFireFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIRE_FLOWER_STATE_APPEAR_LONG_DISTANCE:
		vx = nx * SPEED_OF_FIRE_FLOWER_X;
		vy = ny * SPEED_OF_FIRE_FLOWER_Y;
		break;
	case FIRE_FLOWER_STATE_APPEAR_SHORT_DISTANCE:
		vx = nx * SPEED_OF_FIRE_FLOWER_X;
		vy = ny * SPEED_OF_FIRE_FLOWER_Y;
		break;
	case FIRE_FLOWER_STATE_DISAPPEAR:
		vx = 0;
		vy = 0;
		break;
	}
}