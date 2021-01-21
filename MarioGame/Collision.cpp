
#include "Collision.h"
#include <algorithm>
#include "Utils.h"
#include "ColorBrick.h"
#include "Coin.h"
#include "Mario.h"
#include "Koopas.h"
#include "BrickIntro.h"
#include "BreakableBrick.h"
#include "FireFlower.h"
#include "Boomerang.h"
#include "MovingBrick.h"
#include "Brick.h"
#include "Pipe.h"
#include "FireBall.h"

void CCollisionHandler::SweptAABB(
	double ml, double mt, double mr, double mb,
	double dx, double dy,
	double sl, double st, double sr, double sb,
	double& t, double& nx, double& ny)
{

	double dx_entry, dx_exit, tx_entry, tx_exit;
	double dy_entry, dy_exit, ty_entry, ty_exit;

	double t_entry;
	double t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	double bl = dx > 0 ? ml : ml + dx;
	double bt = dy > 0 ? mt : mt + dy;
	double br = dx > 0 ? mr + dx : mr;
	double bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = (double)-99999999999;
		tx_exit = (double)99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}

LPCOLLISIONEVENT CCollisionHandler::SweptAABBEx(LPGAMEOBJECT coO, LPGAMEOBJECT co1, DWORD dt)
{
	double dx = co1->GetDistanceX();
	double dy = co1->GetDisTanceY();

	double sl, st, sr, sb;		// static object bbox
	double ml, mt, mr, mb;		// moving object bbox
	double t, nx, ny;


	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	double svx, svy;
	coO->GetSpeed(svx, svy);

	double sdx = svx * dt;
	double sdy = svy * dt;

	dx = dx - sdx;
	dy = dy - sdy;

	co1->GetBoundingBox(ml, mt, mr, mb);

	CCollisionHandler::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, dx, dy, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CCollisionHandler::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	LPGAMEOBJECT co1,
	vector<LPCOLLISIONEVENT>& coEvents,
	DWORD dt)
{

	if (dynamic_cast<CKoopas*>(co1))
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			// Khong xu li va cham rua voi lua hoa
			if (dynamic_cast<CFireFlower*>(coObjects->at(i)))
				continue;

			// Khong xu li va cham rua voi Tien breakable brick
			if (dynamic_cast<CBreakableBrick*>(coObjects->at(i)))
			{
				CBreakableBrick* breakbrick = dynamic_cast<CBreakableBrick*>(coObjects->at(i));
				if (breakbrick->GetState() == BREAKBRICK_STATE_COIN)
					continue;
			}

			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i), co1, dt);
			if (e->t > 0 && e->t <= 1.0f)
				coEvents.emplace_back(e);
			else
				delete e;
		}
	}
	else if (dynamic_cast<CBoomerang*>(co1))
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (!dynamic_cast<CMario*> (co1))
				continue;
			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i), co1, dt);
			if (e->t > 0 && e->t <= 1.0f)
				coEvents.emplace_back(e);
			else
				delete e;
		}
	}
	else if (dynamic_cast<CFireBall*>(co1))
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CMario*> (co1))
				continue;
			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i), co1, dt);
			if (e->t > 0 && e->t <= 1.0f)
				coEvents.emplace_back(e);
			else
				delete e;
		}
	}
	else
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CBoomerang*>(coObjects->at(i)) || dynamic_cast<CMovingBrick*>(coObjects->at(i)))
			{
				if (!dynamic_cast<CMario*> (co1))
					continue;
				if (dynamic_cast<CPipe*>(co1))
					continue;
			}
			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i), co1, dt);
			if (e->t > 0 && e->t <= 1.0f)
				coEvents.emplace_back(e);
			else
				delete e;
		}
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CCollisionHandler::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	double& min_tx, double& min_ty,
	double& nx, double& ny, double& rdx, double& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}

		if (dynamic_cast<CColorBrick*>(coEvents[i]->obj))
		{
			nx = 0;
			if (ny == 1)
			{
				ny = 0;
			}
		}
		if (dynamic_cast<CCoin*>(coEvents[i]->obj))
		{
			nx = 0;
			ny = 0;
		}

		if (dynamic_cast<CMovingBrick*>(coEvents[i]->obj))
		{
			ny = -0.00001f;
		}

		if (dynamic_cast<CBreakableBrick*>(coEvents[i]->obj))
		{
			CBreakableBrick* breakbrick = dynamic_cast<CBreakableBrick*>(coEvents[i]->obj);
			if (breakbrick->GetState() == BREAKBRICK_STATE_COIN)
			{
				//DebugOut(L"this is break \n");
				nx = 0;
				ny = -0.0001;
			}
		}
		if (dynamic_cast<CMario*>(coEvents[i]->obj) || dynamic_cast<CKoopas*>(coEvents[i]->obj))
		{
			//nx = 0;
			ny = -0.00001;
		}
	/*	if (dynamic_cast<CMario*>(coEvents[i]->obj))
		{
			nx = 0;
			ny = -0.0001f;
		}*/
	}


	if (min_ix >= 0) coEventsResult.emplace_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.emplace_back(coEvents[min_iy]);
}


bool CCollisionHandler::CheckIntersectCollision(double left_object1, double right_object1, double top_object1, double bottom_object1, double left_object2, double right_object2, double top_object2, double bottom_object2)
{
	if (right_object1 >= left_object2 && right_object2 >= left_object1 && top_object2 <= bottom_object1 && bottom_object2 >= top_object1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

