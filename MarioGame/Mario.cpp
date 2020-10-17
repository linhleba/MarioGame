#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Collision.h"
#include "Koopas.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CCollisionHandler *collisionHandler = new CCollisionHandler();

	coEvents.clear();
	
	// Add left collision
	if (vx < 0 && x < 0) x = 0;

	// Add current right collision
	if (vx > 0 && x > 2496) x = 2496;


	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
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

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0)
		{
			vy = 0;
			if (isJumping == true)
			{
				isJumping = false;
			}
		}


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
			else if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* k = dynamic_cast<CKoopas*>(e->obj);
				if (e->ny < 0)
				{
					if (k->GetState() != KOOPAS_STATE_DIE)
					{
						if (k->GetState() == KOOPAS_STATE_WALKING)
						{
							k->SetState(KOOPAS_STATE_DIE);
							vy = -MARIO_JUMP_DEFLECT_SPEED;
						}
					}
					else if (k->GetState() == KOOPAS_STATE_DIE)
					{
						k->SetState(KOOPAS_STATE_RUNNING_SHELL_RIGHT);
					}

				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (k->GetState() != KOOPAS_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
								SetState(MARIO_STATE_DIE);
						}
						else if (k->GetState() == KOOPAS_STATE_DIE)
						{
							if (nx < 0)
							{
								shoot = -1;
								k->SetState(KOOPAS_STATE_RUNNING_SHELL_RIGHT);
							}
							else
							{
								shoot = 1;
								k->SetState(KOOPAS_STATE_RUNNING_SHELL_LEFT);
							}
						}

					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}



void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		if (level == MARIO_LEVEL_BIG)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
				else ani = MARIO_ANI_BIG_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				ani = MARIO_ANI_BIG_WALKING_RIGHT;
			}
			else
			{
				//DebugOut(L"vx left= %d \n", vx);
				ani = MARIO_ANI_BIG_WALKING_LEFT;
			}

			if (isJumping == true)
			{
				if (nx > 0)
				{
					ani = MARIO_ANI_BIG_JUMPING_RIGHT;
				}
				else
				{
					ani = MARIO_ANI_BIG_JUMPING_LEFT;
				}
			}
			if (shoot == -1)
			{
				ani = MARIO_ANI_BIG_SHOOT_RIGHT;
				float time = GetTickCount();
				if (time > 2000000)
					shoot = 0;
			}
			else if (shoot == 1)
			{
				ani = MARIO_ANI_BIG_SHOOT_LEFT;
				float time = GetTickCount();
				if (time > 2000000)
					shoot = 0;
			}
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				else ani = MARIO_ANI_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = MARIO_ANI_SMALL_WALKING_RIGHT;
			else ani = MARIO_ANI_SMALL_WALKING_LEFT;

			if (isJumping == true)
			{
				if (nx > 0)
				{
					ani = MARIO_ANI_SMALL_JUMPING_RIGHT;
				}
				else
				{
					ani = MARIO_ANI_SMALL_JUMPING_LEFT;
				}
			}
		}
		
		else if (level == MARIO_LEVEL_FIRE)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_FIRE_IDLE_RIGHT;
				else ani = MARIO_ANI_FIRE_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				ani = MARIO_ANI_FIRE_WALKING_RIGHT;
			}
			else
			{
				ani = MARIO_ANI_FIRE_WALKING_LEFT;
			}

			if (isJumping == true)
			{
				if (nx > 0)
				{
					ani = MARIO_ANI_FIRE_JUMPING_RIGHT;
				}
				else
				{
					ani = MARIO_ANI_FIRE_JUMPING_LEFT;
				}
			}
		}

		else if (level == MARIO_LEVEL_TAIL)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_TAIL_IDLE_RIGHT;
				else ani = MARIO_ANI_TAIL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				ani = MARIO_ANI_TAIL_WALKING_RIGHT;
			}
			else
			{
				ani = MARIO_ANI_TAIL_WALKING_LEFT;
			}
			
			if (isJumping == true)
			{
				if (nx > 0)
				{
					ani = MARIO_ANI_TAIL_JUMPING_RIGHT;
				}
				else
				{
					ani = MARIO_ANI_TAIL_JUMPING_LEFT;
				}
			}
		}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED + boostSpeed;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx = -(MARIO_WALKING_SPEED + boostSpeed);
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again (done)
		vy = -MARIO_JUMP_SPEED_Y;
		ny = -1;
		break;
	case MARIO_STATE_IDLE:
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		ny = 1;
		break;
	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_FIRE)
	{
		right = x + MARIO_FIRE_BBOX_WIDTH;
		bottom = y + MARIO_FIRE_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_TAIL)
	{
		right = x + MARIO_TAIL_BBOX_WIDTH;
		bottom = y + MARIO_TAIL_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetIsJumping(bool value)
{
	isJumping = value;
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

