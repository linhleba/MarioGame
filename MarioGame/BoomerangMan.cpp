#include "BoomerangMan.h"
#include "Collision.h"
#include "Game.h"
#include "Boomerang.h"
#include "Mario.h"
#include "PlayScence.h"

CBoomerangMan::CBoomerangMan()
{
	SetState(BOOMERANG_MAN_STATE_MOVE_RIGHT);
	this->layerRender = 1;
	this->nx = 1;
}

void CBoomerangMan::Render()
{
	int ani = -1;

	if (state != BOOMERANG_MAN_STATE_DIE)
	{
		if (checkThrowingBoomerang)
		{
			if (nx > 0)
				ani = BOOMERANG_MAN_ANI_THROW_BOOMERANG_RIGHT;
			else
			{
				ani = BOOMERANG_MAN_ANI_THROW_BOOMERANG_LEFT;
			}
		}
		else
		{
			if (nx > 0)
				ani = BOOMERANG_MAN_ANI_NORMAL_RIGHT;
			else
			{
				ani = BOOMERANG_MAN_ANI_NORMAL_LEFT;
			}
		}
	}
	else
	{
		if (nx > 0)
			ani = BOOMERANG_MAN_ANI_DIE_RIGHT;
		else
			ani = BOOMERANG_MAN_ANI_DIE_LEFT;
	}
	if (ani != -1)
	{
		animation_set->at(ani)->Render(x, y);
	}
}

void CBoomerangMan::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = x;
	t = y;
	r = l + BOOMERANG_MAN_BBOX_WIDTH;
	b = t + BOOMERANG_MAN_BBOX_HEIGHT;
}

void CBoomerangMan::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOOMERANG_MAN_STATE_MOVE_RIGHT:
		vx = 0.03f;
		vy = 0;
		break;
	case BOOMERANG_MAN_STATE_MOVE_LEFT:
		vx = -0.03f;
		vy = 0;
		break;
	case BOOMERANG_MAN_STATE_IDLE:
		vx = 0;
		vy = 0.02f;
		break;
	case BOOMERANG_MAN_STATE_DIE:
		vx = 0;
		break;
	}
}

void CBoomerangMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//DebugOut(L"state boomerang is %d \n", this->GetState());
	// Set gravity for boomerangman
	vy += BOOMERANG_MAN_GRAVITY * dt;


	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();



	if (mario->x - this->x >= 18)
	{
		if (state != BOOMERANG_MAN_STATE_DIE)
		{
			nx = 1;
		}
	}
	else if ((mario->x - this->x <= -1))
	{
		if (state != BOOMERANG_MAN_STATE_DIE)
		{
			nx = -1;
		}
	}
	// Set to check diff time
	if (preTime_start == 0)
	{
		preTime_start = GetTickCount();
	}
	else
	{
		if (GetTickCount() - preTime_start <= 50)
		{
			preTime_start = GetTickCount();
		}
		else
		{
			diff_time = GetTickCount() - preTime_start;
			preTime_start = GetTickCount();
		}
	}

	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (state != BOOMERANG_MAN_STATE_DIE)
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);

	if (state != BOOMERANG_MAN_STATE_DIE)
	{
		if (GetTickCount() - timeRenderingThrowing_start >= 300)
		{
			checkThrowingBoomerang = false;
			timeRenderingThrowing_start = 0;
		}

		if (isChangeState == false)
		{
			isChangeState = true;
			isChangeState_start = GetTickCount();
		}
		else
		{
			if (GetTickCount() - isChangeState_start >= 700 + diff_time)
			{
				SetState(BOOMERANG_MAN_STATE_MOVE_RIGHT);
			}

			if (GetTickCount() - isChangeState_start >= 2000 + diff_time)
			{
				SetState(BOOMERANG_MAN_STATE_IDLE);
			}
			if (GetTickCount() - isChangeState_start >= 2700 + diff_time)
			{
				SetState(BOOMERANG_MAN_STATE_MOVE_LEFT);
			}

			if (GetTickCount() - isChangeState_start >= 4000 + diff_time)
			{
				SetState(BOOMERANG_MAN_STATE_IDLE);
				isChangeState = false;
				//sub_time = 0;
			}
		}

		for (size_t i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT coObject = coObjects->at(i);
			if (dynamic_cast<CBoomerang*>(coObject))
			{
				CBoomerang* boomerang = dynamic_cast<CBoomerang*>(coObject);
				// Check if Boomerang is type 1 or 2
				if (boomerang->GetTypeOfBoomerang() == OBJECT_TYPE_BOOMERANG_1)
				{
					if (!boomerang->GetIsUsing())
					{
						if (GetTickCount() - isChangeState_start >= 900 + diff_time)
						{
							if (this->nx > 0)
								boomerang->nx = 1;
							else
								boomerang->nx = -1;

							checkThrowingBoomerang = true;
							boomerang->SetState(BOOMERANG_STATE_FLYING_TOP);

							// Set time to render the ani throwing
							//checkTimeRenderingThrowing = true;
							SetTimeRenderThrowing();

							// Set time to change state for boomerang
							boomerang->SetTimeForBoomerang();
							// Set boomerang is using to can't get again while using
							boomerang->SetIsUsing(true);

							// Set position for boomerang
							boomerang->SetPosition(x - 8, y - 5);
						}
					}
				}
				else
				{
					if (!boomerang->GetIsUsing())
					{
						if (GetTickCount() - isChangeState_start >= 3300 + diff_time)
						{
							if (this->nx > 0)
								boomerang->nx = 1;
							else
								boomerang->nx = -1;

							checkThrowingBoomerang = true;
							boomerang->SetState(BOOMERANG_STATE_FLYING_TOP);

							// Set time to render the ani throwing
							//checkTimeRenderingThrowing = true;
							SetTimeRenderThrowing();

							// Set time to change state for boomerang
							boomerang->SetTimeForBoomerang();
							// Set boomerang is using to can't get again while using
							boomerang->SetIsUsing(true);

							// Set position for boomerang
							boomerang->SetPosition(x - 8, y - 5);
						}
					}
				}
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

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		
		if (ny != 0)
			vy = 0;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
