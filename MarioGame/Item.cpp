#include "Item.h"
#include "Utils.h"
#include "Collision.h"

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	if (typeItem == 2)
	{
		y += 0.03 * dt;
	}
	else if (typeItem == 1)
	{
		//y += 0.008 * dt;
		vy += 0.008 * dt;
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
			collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			// block object
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;
			if (nx != 0 && ny == 0)
			{
				vx = -vx;
			}
			if (ny != 0)
			{
				vy = 0;
			}
		}
	}
}


void CItem::Render()
{
	if (isAppear)
	{
		DebugOut(L"type item la: %d \n", typeItem);
		if (typeItem == 1)
		{
			animation_set->at(0)->Render(x, y);
		}
		else if (typeItem == 2)
		{
			animation_set->at(1)->Render(x, y);
		}
	}
	//RenderBoundingBox();
}
void CItem::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_MUSHROOM_APPEAR:
		vx = 0.08f;
		break;
	}

}

void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + ITEM_BBOX_WIDTH;
	b = y + ITEM_BBOX_HEIGHT;
}