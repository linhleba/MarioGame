#include "Question.h"
#include "Collision.h"
#include "Mario.h"
#include "Item.h"
#include "PlayScence.h"
CQuestion::CQuestion()
{
	SetState(QUESTION_STATE_MOVEMENT);
}

int CQuestion::CheckPositionQuestion()
{
	if (x == 241)
	{
		return 1;
	}
	else if (x == 656)
	{
		return 2;
	}
	else if (x == 1472)
	{
		return 3;
	}
	else
	{
		return -1;
	}
}

void CQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	coEvents.clear();
	collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);

	int qPosition;
	qPosition = CheckPositionQuestion();
	if (qPosition != -1 && state == QUESTION_STATE_BLANK)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CItem*>(obj))
			{
				CItem* item = dynamic_cast<CItem*>(obj);
				CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
				int iPosition;
				iPosition = item->CheckPositionItem();
				if (iPosition == qPosition)
				{
					if (mario->GetLevel() >= MARIO_LEVEL_BIG)
					{
						item->SetState(ITEM_STATE_LEAF_APPEAR);
					}
					else
					{
						item->SetState(ITEM_STATE_MUSHROOM_APPEAR);
					}
				}
			}
		}
	}
	if (coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* k = dynamic_cast<CKoopas*>(e->obj);
				if (k->GetState() == KOOPAS_STATE_RUNNING_SHELL_LEFT || k->GetState() == KOOPAS_STATE_RUNNING_SHELL_RIGHT)
				{
					if (nx != 0 && ny == 0)
					{
						SetState(QUESTION_STATE_BLANK);
					}
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