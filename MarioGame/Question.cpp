#include "Question.h"
#include "Collision.h"
#include "Mario.h"
#include "Item.h"
#include "PlayScence.h"
CQuestion::CQuestion()
{
	SetState(QUESTION_STATE_APPEAR);
}

CQuestion::CQuestion(int type)
{
	typeOfQuestion = type;
	SetState(QUESTION_STATE_APPEAR);
}

bool CQuestion::CheckQuestionHasMushRoom(vector<LPGAMEOBJECT>* coObjects)
{
	for (size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CItem*>(obj))
		{
			CItem* item = dynamic_cast<CItem*>(obj);
			if (this->x == item->x && this->y == item->y)
				return true;
		}
	}
	return false;

}

void CQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	coEvents.clear();
	collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	// Update state to handle coin brick
	if (state == QUESTION_STATE_MOVEMENT)
	{
		if (typeOfQuestion == OBJECT_TYPE_SPECIAL_COIN_BRICK)
		{
			if (countTimeGetCoin < 10)
			{
				if (isMovingUp)
				{
					// set the down value again if the time set up greater than 400
					if (countTimeUp > 4)
					{
						isMovingUp = false;
					}

					// set y little up when time is less than 400
					else
					{
						y -= 1;
						countTimeUp++;
					}
				}
				else
				{
					if (countTimeUp != 0)
					{
						y += 1;
						countTimeUp--;
					}
					else
					{
						isMovingUp = true;
						countTimeGetCoin++;
						SetState(QUESTION_STATE_APPEAR);
					}
				}
			}
			else
			{
				SetState(QUESTION_STATE_BLANK);
			}
		}
	}

	// check if question is equal the position of item
	bool qPosition = CheckQuestionHasMushRoom(coObjects);
	if (qPosition == true && state == QUESTION_STATE_BLANK)
	{
		for (size_t i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CItem*>(obj))
			{
				CItem* item = dynamic_cast<CItem*>(obj);
				CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

				// special spped for level up
				if (mario->GetLevel() >= MARIO_LEVEL_BIG)
				{
					if (!isUsed)
					{
						if (item->GetTypeOfItem() == OBJECT_TYPE_GREEN_MUSHROOM)
						{
							item->SetState(ITEM_STATE_MUSHROOM_APPEAR);
							isUsed = true;
						}
						else
						{
							if (mario->GetLevel() == MARIO_LEVEL_BIG)
							{
								item->SetState(ITEM_STATE_LEAF_APPEAR);
							}
							else if (mario->GetLevel() == MARIO_LEVEL_TAIL)
							{
								item->SetState(ITEM_STATE_FIRE_FLOWER_APPEAR);
							}
							else
							{
								item->SetState(ITEM_STATE_LEAF_APPEAR);
							}
							isUsed = true;
						}
					}
				}
				else
				{
					if (!isUsed)
					{
						item->SetState(ITEM_STATE_MUSHROOM_APPEAR);
						isUsed = true;
					}
				}
			}
		}
	}

	if (qPosition == false && state == QUESTION_STATE_BLANK)
	{
		if (isMovingUp)
		{
			// set the down value again if the time set up greater than 400
			if (countTimeUp > 4)
			{
				isMovingUp = false;
			}

			// set y little up when time is less than 400
			else
			{
				y -= 1;
				countTimeUp++;
			}
		}
		else
		{
			if (countTimeUp != 0)
			{
				y += 1;
				countTimeUp--;
			}
		}
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

	if (state == QUESTION_STATE_APPEAR)
	{
		switch (typeOfQuestion)
		{
		case OBJECT_TYPE_QUESTION:
			ani = QUESTION_ANI_MOVEMENT;
			break;
		case OBJECT_TYPE_SPECIAL_BRICK:
			ani = QUESTION_ANI_SPECIAL_BRICK;
			break;
		case OBJECT_TYPE_SPECIAL_COIN_BRICK:
			ani = QUESTION_ANI_SPECIAL_BRICK;
			break;
		}
	}
	else if (state == QUESTION_STATE_BLANK)
	{
		ani = QUESTION_ANI_BLANK;
	}
	else if (state == QUESTION_STATE_MOVEMENT)
	{
		if (typeOfQuestion == OBJECT_TYPE_SPECIAL_COIN_BRICK)
		{
			ani = QUESTION_ANI_SPECIAL_BRICK;
		}
	}
	if (ani != -1)
		animation_set->at(ani)->Render(x, y);
}

void CQuestion::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = x;
	t = y;
	r = x + QUESTION_BBOX_WIDTH;
	b = y + QUESTION_BBOX_HEIGHT;
}