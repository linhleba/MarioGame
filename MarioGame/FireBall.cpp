#include "FireBall.h"
#include "Collision.h"

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += 0.00008 * dt;
	vx += 0.00008 * dt;
	CGameObject::Update(dt, coObjects);
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
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
		} 
		else if (nx != 0)
		{
			nx = -nx;
		}
	}
}
void CFireBall::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBALL_BBOX_WIDTH;
	b = y + FIREBALL_BBOX_HEIGHT;
}