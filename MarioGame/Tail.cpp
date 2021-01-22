#include "Tail.h"
#include "Collision.h"
#include "Mario.h"
#include "Koopas.h"
#include "Goomba.h"
#include "Flower.h"
#include "BreakableBrick.h"
#include "PlayScence.h"
#include "Game.h"
#include "Fragments.h"
#include "Question.h"
#include "HitEffect.h"

CTail::CTail()
{
	SetState(TAIL_STATE_DISAPPEARING);
}

void CTail::Render()
{
	//animation_set->at(TAIL_ANI_MOVING)->Render(x, y);
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	CMario* mario = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();

	nx = mario->nx;

	// Check state is HitEffect
	if (isHitEffect)
	{
		for (size_t i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CHitEffect*>(obj))
			{
				CHitEffect* hitEffect = dynamic_cast<CHitEffect*>(obj);
				hitEffect->SetPosition(this->x + 5, this->y - 10);
				hitEffect->SetState(HIT_EFFECT_TAIL_STATE_APPEAR);
				isHitEffect = false;
			}
		}
	}


	if (state == TAIL_STATE_DISAPPEARING)
	{
		isTailing = false;
	}
	if (state == TAIL_STATE_MOVING)
	{
		if (!isTailing)
		{
			isTailing = true;
			timeTailing_start = GetTickCount();
		}
		else
		{
			if (GetTickCount() - timeTailing_start > 55)
			{
				isTailing = false;
				SetState(TAIL_STATE_DISAPPEARING);
			}
		}
	}

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
				if (dynamic_cast<CMario*>(e->obj) || dynamic_cast<CBrick*>(e->obj))
				{
					nx = 0;
					ny = 0;
				}
				else
				{
					if (dynamic_cast<CKoopas*>(e->obj))
					{
						CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
						koopas->SetIsFaceUp(true);
						if (koopas->GetState() == KOOPAS_STATE_WALKING || koopas->GetState() == KOOPAS_STATE_FLYING)
						{
							koopas->SetState(KOOPAS_STATE_DIE);
						}
						else if (koopas->GetState() == KOOPAS_STATE_DIE || koopas->GetState() == KOOPAS_STATE_RUNNING_SHELL_RIGHT
							|| koopas->GetState() == KOOPAS_STATE_RUNNING_SHELL_LEFT)
						{
							koopas->nx = int(nx);
							koopas->SetState(KOOPAS_STATE_DIE_FALL);
						}
						isHitEffect = true;
					}
					if (dynamic_cast<CGoomba*>(e->obj))
					{
						CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
						if (goomba->GetState() == GOOMBA_STATE_WALKING)
						{
							goomba->SetDieDir(this->x);
							goomba->SetState(GOOMBA_STATE_DIE_REFLECTION);
							//goomba->SetGoombaDie();
							//goomba->SetTickCount();
						}
						isHitEffect = true;
					}
					if (dynamic_cast<CQuestion*>(e->obj))
					{
						CQuestion* question = dynamic_cast<CQuestion*>(e->obj);
						/*if (question->GetState() == QUESTION_STATE_MOVEMENT)
						{*/
							question->SetState(QUESTION_STATE_BLANK);
						//}
					}
					if (dynamic_cast<CFlower*>(e->obj))
					{
						CFlower* flower = dynamic_cast<CFlower*>(e->obj);
						flower->SetState(FLOWER_STATE_DIE);
						isHitEffect = true;
					}
					if (dynamic_cast<CBreakableBrick*>(e->obj))
					{
						CBreakableBrick* breakbrick = dynamic_cast<CBreakableBrick*>(e->obj);
						if (breakbrick->GetState() == BREAKBRICK_STATE_APPEAR)
						{
							breakbrick->SetState(BREAKBRICK_STATE_DISAPPEAR);
						}
					}
					SetState(TAIL_STATE_DISAPPEARING);
				}
			}

			// block object
			y += min_ty * dy + ny * 0.4f;
			x += min_tx * dx + nx * 0.4f;
		}
}

void CTail::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	if (state != TAIL_STATE_DISAPPEARING)
	{
		l = x;
		t = y;
		r = x + TAIL_BBOX_WIDTH;
		b = y + TAIL_BBOX_HEIGHT;
	}
	else
	{
		l = t = r = b = 0;
	}

}

void CTail::SetState(int state)
{
	switch (state)
	{
	case TAIL_STATE_DISAPPEARING:
		vx = vy = 0;
		break;
	case TAIL_STATE_MOVING:
		vx = nx * SPEED_OF_MOVING_TAIL;
		vy = 0;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}
