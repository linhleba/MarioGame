#include "Question.h"
#include "Collision.h"
#include "Mario.h"
CQuestion::CQuestion()
{
	SetState(QUESTION_STATE_MOVEMENT);
}

void CQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	coEvents.clear();
	collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);

	if (coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CMario*>(e->obj))
			{
				//float mleft, mtop, mright, mbottom;
				//e->obj->GetBoundingBox(mleft, mtop, mright, mbottom);
				if (ny < 0 && nx == 0)
				{
					SetState(QUESTION_STATE_BLANK);
				}
			}
		}
	}
}

void CQuestion::Render()
{
	int ani = -1;

	if (state == QUESTION_STATE_MOVEMENT)
	{
		ani = QUESTION_ANI_MOVEMENT;
	}
	else if (state == QUESTION_STATE_BLANK)
	{
		ani = QUESTION_ANI_BLANK;
	}
	animation_set->at(ani)->Render(x, y);
}

void CQuestion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + QUESTION_BBOX_WIDTH;
	b = y + QUESTION_BBOX_HEIGHT;
}