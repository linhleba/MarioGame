#include "FireBall.h"
#include "Collision.h"
#include "Mario.h"
#include "Koopas.h"
#include "Goomba.h"

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//vy += 0.0008 * dt;
	//vx += 0.00008 * dt;
	CGameObject::Update(dt, coObjects);
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (y < topBoundary && vy < 0)
		{
			vy = -vy;
		}
	}
	else
	{
		

		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (ny != 0)
		{
			vy = -vy;
			if (ny > 0)
			{
				topBoundary = y;
			}
		}
		else if (nx != 0)
		{
			vx = 0;
			isFiring = false;
		}

		

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CMario*>(e->obj))
			{
				nx = 0;
				ny = 0;
			}
			if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				if (nx != 0)
				{
					if (koopas->GetState() == KOOPAS_STATE_WALKING)
					{
						koopas->SetState(KOOPAS_STATE_DIE);
					}
					else if (koopas->GetState() == KOOPAS_STATE_DIE || koopas->GetState() == KOOPAS_STATE_RUNNING_SHELL_RIGHT
				     || koopas->GetState() == KOOPAS_STATE_RUNNING_SHELL_LEFT)
					{
						koopas->SetState(KOOPAS_STATE_DIE_FALL);
					}
				}
			}
			if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				if (nx != 0)
				{
					if (goomba->GetState() == GOOMBA_STATE_WALKING)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						goomba->SetGoombaDie();
						goomba->SetTickCount();
					}
				}
			}
		}

		// block object
		y += min_ty * dy + ny * 0.4f;
		x += min_tx * dx + nx * 0.4f;
	}
}
void CFireBall::Render()
{
	if (isFiring == true)
	{
		animation_set->at(0)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFiring)
	{
		l = x;
		t = y;
		r = x + FIREBALL_BBOX_WIDTH;
		b = y + FIREBALL_BBOX_HEIGHT;
	}
	else
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}