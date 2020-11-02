#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Collision.h"
#include "Koopas.h"
#include "ColorBrick.h"
#include "Coin.h"
#include "FireBall.h"

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
	CCollisionHandler* collisionHandler = new CCollisionHandler();


	// Intersect logic collision with Koopas
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CKoopas*>(obj)) {

			float kLeft, kTop, kRight, kBottom, mLeft, mTop, mRight, mBottom;
			obj->GetBoundingBox(kLeft, kTop, kRight, kBottom);
			if (state != MARIO_STATE_TURN)
			{
				GetBoundingBox(mLeft, mTop, mRight, mBottom);
			}
			else
			{
				mLeft = 0;
				mRight = 0;
				mTop = 0;
				mBottom = 0;
			}
			//DebugOut(L"holding la: %d \n", isHolding);

			//if (collisionHandler->CheckIntersectCollision(mLeft, mRight, mTop, mBottom, kLeft - 5, kRight + 5, kTop, kBottom)) // set a little bounding box for mario
			//{
			//	if (isHolding && obj->GetState() == KOOPAS_STATE_DIE)
			//	{
			//		flagHolding = true;
			//		if (level != MARIO_LEVEL_SMALL)
			//		{
			//			obj->SetPosition(this->x + this->nx * 12, this->y + 8);
			//		}
			//		else
			//		{
			//			obj->SetPosition(this->x + this->nx * 10, this->y - 1); // move a little for mario to hold tightly
			//		}
			//	}
			//	else
			//	{
			//		flagHolding = false;
			//		if (obj->GetState() == KOOPAS_STATE_DIE)
			//		{
			//			shoot = -nx;
			//			obj->SetState(KOOPAS_STATE_RUNNING_SHELL_RIGHT);
			//			obj->SetPosition(this->x, this->y);
			//			obj->SetSpeed(this->nx * 0.25f, obj->vy);
			//		}
			//	}
			//}
			//else
			//{
			//	flagHolding = false;
			//}

		}
		if (dynamic_cast<CFireBall*>(obj))
		{
			CFireBall* fireball = dynamic_cast<CFireBall*>(obj);

			// fireball was used will not be used again
			if (shootFire && fireball->GetIsFiring() == false)
			{
				fireball->SetPosition(this->x, this->y);
				fireball->SetTopBoundary(this->y);
				fireball->SetSpeed(nx * 0.15f, 0.12f);
				fireball->SetIsFiring(true);
				shootFire = false;
			}
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();


	// Add left collision
	if (vx < 0 && x < 0) x = 0;

	// Add current right collision
	if (vx > 0 && x > 2806) x = 2806;



	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	// update acceleration of Mario

	if (state == MARIO_STATE_WALKING_RIGHT || state == MARIO_STATE_WALKING_LEFT || state == MARIO_STATE_HIGH_SPEED_RIGHT
		|| state == MARIO_STATE_HIGH_SPEED_LEFT)
	{
		DebugOut(L"van toc la  %d \n", vx);
		DebugOut(L"nx la %d \n", nx);
		if (abs(vx) < MARIO_MIN_WALKING_SPEED)
		{
			vx = nx * (MARIO_MIN_WALKING_SPEED + boostSpeed);
		}

		else if (abs(vx) > MARIO_MAX_WALKING_SPEED)
		{
			vx = nx * (MARIO_MAX_WALKING_SPEED + boostSpeed);
		}
		else
		{
			vx +=  nx * (MARIO_ACCELERATION_SPEED * dt);
		}
		//vx = 0.12f;
	}

	else if (state == MARIO_STATE_IDLE)
	{
		if (vx > 0.05)
		{
			vx = vx - dt * MARIO_ACCELERATION_SPEED;
		}
		else if (vx < -0.05)
		{
			vx = vx + dt * MARIO_ACCELERATION_SPEED;
		}
		else
		{
			vx = 0;
		}
	}

	// check condition for flying state and fall state
	if (CheckStateFlying())
	{
		if (state == MARIO_STATE_FLYING_RIGHT || state == MARIO_STATE_FALL_RIGHT)
		{
			vx = MARIO_FLYING_SPEED;
		}
		else if (state == MARIO_STATE_FLYING_LEFT || state == MARIO_STATE_FALL_LEFT)
		{
			vx = -MARIO_FLYING_SPEED;
		}
		else
		{
			vx = 0;
		}
	}

	// Check to stop mario turning back
	if (state == MARIO_STATE_TURN)
	{
		if (GetTickCount() - turnBackTail_start > 250)
		{
			SetState(MARIO_STATE_IDLE);
		}
	}

	// Check to run high speed for mario
	if (hasHighSpeed && state != MARIO_STATE_IDLE)
	{
		DebugOut(L"boostspeed %d \n", boostSpeed);
		//DebugOut(L"gia tri %d \n", GetTickCount() - highSpeed_start);
		if (GetTickCount() - highSpeed_start > 1500)
		{
			if (nx > 0)
				SetState(MARIO_STATE_HIGH_SPEED_RIGHT);
			else
				SetState(MARIO_STATE_HIGH_SPEED_LEFT);
		}
	}

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

		//if (nx != 0) vx = 0;

		// check jump if state is different with mario state fly
		if (ny != 0 && !CheckStateFlying())
		{
			vy = 0;
			if (isJumping == true)
			{
				isJumping = false;
			}
		}

		// Chec when Mario fall and collide with the ground
		if (ny != 0 && !CheckStateFlying())
		{
			isFlying_start = GetTickCount();
			startFlying = false;
		}


		// Collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// set state idle when collision, if collision is Coin and ColorBrick - Mario continue flying
			if (CheckStateFlying())
			{
				if (!dynamic_cast<CCoin*>(e->obj) && !dynamic_cast<CColorBrick*>(e->obj))
				{
					SetState(MARIO_STATE_IDLE);
				}
			}

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() == GOOMBA_STATE_WALKING)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						goomba->SetGoombaDie();
						goomba->SetTickCount();

						vy = -MARIO_JUMP_DEFLECT_SPEED;

					}

				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() == GOOMBA_STATE_WALKING)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								// Update mario tail and turning tail won't die
								if (level == MARIO_LEVEL_TAIL && state == MARIO_STATE_TURN)
								{
									goomba->SetState(GOOMBA_STATE_DIE);
									goomba->SetGoombaDie();
									goomba->SetTickCount();
								}
								else
								{
									level = MARIO_LEVEL_SMALL;
									StartUntouchable();
								}
							}
							else
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CCoin*>(e->obj))
			{
				CCoin* coin = dynamic_cast<CCoin*>(e->obj);
				coin->SetState(COIN_STATE_DISAPPEAR);

			}

			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}

			// Check Koopas
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
							if (level > MARIO_LEVEL_SMALL && state != MARIO_STATE_TURN)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else if (state == MARIO_STATE_TURN)
							{
								k->SetState(KOOPAS_STATE_DIE);
							}
							else
								SetState(MARIO_STATE_DIE);
						}
						else if (k->GetState() == KOOPAS_STATE_DIE)
						{
							if (isHolding != true)
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
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}



void CMario::Render()
{
	DebugOut(L"state la: %d \n", state);
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		if (level == MARIO_LEVEL_BIG)
		{
			if (state == MARIO_STATE_HIGH_SPEED_LEFT || state == MARIO_STATE_HIGH_SPEED_RIGHT)
			{
				if (state == MARIO_STATE_HIGH_SPEED_LEFT)
				{
					ani = MARIO_ANI_BIG_HIGHSPEED_LEFT;
				}
				else
				{
					ani = MARIO_ANI_BIG_HIGHSPEED_RIGHT;
				}
			}
			else if (vx == 0)
			{
				if (flagHolding == true)
				{
					if (nx > 0)
					{
						ani = MARIO_ANI_BIG_HOLD_RIGHT_IDLE;
					}
					else ani = MARIO_ANI_BIG_HOLD_LEFT_IDLE;
				}
				else
				{
					if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_IDLE_LEFT;
				}
			}

			// Set holding for mario
			else if (flagHolding == true)
			{
				if (vx > 0)
				{
					ani = MARIO_ANI_BIG_HOLD_RIGHT_WALK;
				}
				else if (vx < 0)
				{
					ani = MARIO_ANI_BIG_HOLD_LEFT_WALK;
				}

			}
			else
			{

				// Set animation braking when vx is oppsite with nx
				if (nx > 0)
				{
					if (vx < 0)
					{
						ani = MARIO_ANI_BIG_BRAKING_LEFT;
					}
					else
					{
						if (isRunning)
						{
							ani = MARIO_ANI_BIG_RUNNING_RIGHT;
						}
						else
						{
							ani = MARIO_ANI_BIG_WALKING_RIGHT;
						}
					}
				}
				else {
					if (vx > 0)
					{
						ani = MARIO_ANI_BIG_BRAKING_RIGHT;
					}
					else
					{
						if (isRunning)
						{
							//DebugOut(L"is running");
							ani = MARIO_ANI_BIG_RUNNING_LEFT;
						}
						else
						{
							ani = MARIO_ANI_BIG_WALKING_LEFT;
						}
					}
				}

			}

			if (isJumping == true)
			{
				if (state != MARIO_STATE_HIGH_SPEED_LEFT && state != MARIO_STATE_HIGH_SPEED_RIGHT)
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
				else
				{
					if (nx > 0)
					{
						ani = MARIO_ANI_BIG_FLY_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FLY_LEFT;
					}
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
			else
			{
				//DebugOut(L"van toc la: %d \n", vx);

			// Set animation braking when vx is oppsite with nx
				if (nx > 0)
				{
					if (vx < 0)
					{
						ani = MARIO_ANI_SMALL_BRAKING_LEFT;
					}
					else
					{
						ani = MARIO_ANI_SMALL_WALKING_RIGHT;
					}
				}
				else {
					if (vx > 0)
					{
						ani = MARIO_ANI_SMALL_BRAKING_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_SMALL_WALKING_LEFT;
					}
				}

			}


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

			else
			{
				//DebugOut(L"van toc la: %d \n", vx);

			// Set animation braking when vx is oppsite with nx
				if (nx > 0)
				{
					if (vx < 0)
					{
						ani = MARIO_ANI_FIRE_BRAKING_LEFT;
					}
					else
					{
						ani = MARIO_ANI_FIRE_WALKING_RIGHT;
					}
				}
				else {
					if (vx > 0)
					{
						ani = MARIO_ANI_FIRE_BRAKING_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_FIRE_WALKING_LEFT;
					}
				}

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
			if (CheckStateFlying())
			{
				if (!CheckStateFall())
				{
					if (nx > 0)
					{
						if (vy < 0)
						{
							ani = MARIO_ANI_TAIL_FLYING_RIGHT_TOP;
						}
						else
						{
							ani = MARIO_ANI_TAIL_FLYINNG_RIGHT_BOTTOM;
						}
					}
					else if (nx < 0)
					{
						if (vy < 0)
						{
							ani = MARIO_ANI_TAIL_FLYING_LEFT_TOP;
						}
						else
						{
							ani = MARIO_ANI_TAIL_FLYING_LEFT_BOTTOM;
						}
					}
				}
				else
				{
					if (nx > 0)
					{
						if (checkFall)
						{
							ani = MARIO_ANI_TAIL_FALL_RIGHT_TOP;
						}
						else
						{
							ani = MARIO_ANI_TAIL_FALL_RIGHT_BOTTOM;
						}
					}
					else if (nx < 0)
					{
						if (checkFall)
						{
							ani = MARIO_ANI_TAIL_FALL_LEFT_TOP;
						}
						else
						{
							ani = MARIO_ANI_TAIL_FALL_LEFT_BOTTOM;
						}
					}
				}
			}
			else if (state == MARIO_STATE_TURN)
			{
				if (nx > 0)
				{
					ani = MARIO_ANI_TAIL_TURNING_RIGHT;
				}
				else
				{
					ani = MARIO_ANI_TAIL_TURNING_LEFT;
				}
			}
			else if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_TAIL_IDLE_RIGHT;
				else ani = MARIO_ANI_TAIL_IDLE_LEFT;
			}
			else
			{
				//DebugOut(L"van toc la: %d \n", vx);

			// Set animation braking when vx is oppsite with nx
				if (nx > 0)
				{
					if (vx < 0)
					{
						ani = MARIO_ANI_TAIL_BRAKING_LEFT;
					}
					else
					{
						if (isHolding)
						{
							ani = MARIO_ANI_TAIL_RUNNING_RIGHT;
						}
						else
						{
							ani = MARIO_ANI_TAIL_WALKING_RIGHT;
						}
					}
				}
				else {
					if (vx > 0)
					{
						ani = MARIO_ANI_TAIL_BRAKING_RIGHT;
					}
					else
					{
						if (isHolding)
						{
							ani = MARIO_ANI_TAIL_RUNNING_LEFT;
						}
						else
						{
							ani = MARIO_ANI_TAIL_WALKING_LEFT;
						}
					}
				}

			}


			if (isJumping == true && !CheckStateFlying())
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

			// update animation for flying
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
		/*case MARIO_STATE_BRAKE:
				this->SetState(MARIO_STATE_WALKING_LEFT);*/
		break;
	case MARIO_STATE_WALKING_RIGHT:
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		nx = -1;
		break;
	case MARIO_STATE_HIGH_SPEED_LEFT:
		nx = -1;
		break;
	case MARIO_STATE_HIGH_SPEED_RIGHT:
		nx = 1;
		break;
	case MARIO_STATE_JUMP_HIGH_SPEED:
		DebugOut(L"This here");
		vy = -MARIO_JUMP_HIGH_SPEED_Y;
		ny = -1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again (done)
		vy = -MARIO_JUMP_SPEED_Y;
		ny = -1;
		break;
	case MARIO_STATE_IDLE:
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		ny = 1;
		break;
	case MARIO_STATE_FLYING_RIGHT:
		//vy = -MARIO_FLY_SPEED_Y;
		nx = 1;
		break;
	case MARIO_STATE_FLYING_LEFT:
		nx = -1;
		break;
	case MARIO_STATE_FLYING_IDLE:
		vy = -MARIO_FLY_SPEED_Y;
		break;
	case MARIO_STATE_FALL_RIGHT:
		nx = 1;
		break;
	case MARIO_STATE_FALL_LEFT:
		nx = -1;
		break;
	case MARIO_STATE_FALL_IDLE:
		vy = MARIO_GRAVITY - 0.0019999;
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
		// update turning tail
		if (state == MARIO_STATE_TURN)
		{
			right = x + MARIO_TAIL_BBOX_WIDTH * 2.5;
			bottom = y + MARIO_TAIL_BBOX_HEIGHT;
		}
		else if (nx > 0)
		{
			left = left + 8;
			right = x + 8 + MARIO_TAIL_BBOX_WIDTH;
			bottom = y + MARIO_TAIL_BBOX_HEIGHT;
		}
		else
		{
			right = x + MARIO_TAIL_BBOX_WIDTH;
			bottom = y + MARIO_TAIL_BBOX_HEIGHT;
		}
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

bool CMario::CheckStateFlying()
{
	return (state == MARIO_STATE_FLYING_LEFT || state == MARIO_STATE_FLYING_RIGHT || state == MARIO_STATE_FLYING_IDLE
		|| state == MARIO_STATE_FALL_IDLE || state == MARIO_STATE_FALL_RIGHT || state == MARIO_STATE_FALL_LEFT);
}

bool CMario::CheckStateFall()
{
	return (state == MARIO_STATE_FALL_IDLE || state == MARIO_STATE_FALL_LEFT || state == MARIO_STATE_FALL_RIGHT);
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