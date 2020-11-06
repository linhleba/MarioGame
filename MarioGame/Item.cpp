#include "Item.h"
#include "Utils.h"
#include "Collision.h"
#include "Mario.h"

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	// state leaf when big mario
	if (state == ITEM_STATE_LEAF_APPEAR)
	{
		y += 0.03 * dt;
	}
	// state mushroom when small mario
	else if (state == ITEM_STATE_MUSHROOM_APPEAR)
	{
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

			// Check collision nx to change direction
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
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CItem::Render()
{
	if (state == ITEM_STATE_MUSHROOM_APPEAR)
	{
		animation_set->at(ITEM_ANI_MUSHROOM)->Render(x, y);
	}
	else if (state == ITEM_STATE_LEAF_APPEAR)
	{
		animation_set->at(ITEM_ANI_LEAF)->Render(x, y);
	}
	RenderBoundingBox();
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

int CItem::CheckPositionItem()
{
	if (x == 241 && y == 18)
	{
		return 1;
	}
	else if (x == 656 && y == 93)
	{
		return 2;
	}
	else if (x == 1472 && y == 82)
	{
		return 3;
	}
	else
	{
		return -1;
	}
}

void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == ITEM_STATE_MUSHROOM_APPEAR || state == ITEM_STATE_LEAF_APPEAR)
	{
		l = x;
		t = y;
		r = x + ITEM_BBOX_WIDTH;
		b = y + ITEM_BBOX_HEIGHT;
	}
	else
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}