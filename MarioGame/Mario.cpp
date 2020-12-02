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
#include "Item.h"
#include "Question.h"
#include "Flower.h"
#include "FireFlower.h"
#include "BreakableBrick.h"

CMario::CMario(double x, double y) : CGameObject()
{
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	SetGeneralAniBigMario(generalAniBigMario);
	SetGeneralAniSmallMario(generalAniSmallMario);
	SetGeneralAniFireMario(generalAniFireMario);
	SetGeneralAniTailMario(generalAniTailMario);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	HandleNoCollision(coObjects);

	// Add left collision
	if (vx < 0 && x < 0) x = 0;

	// Add current right collision
	if (vx > 0 && x > 2806) x = 2806;
	
	HandleState();
	HandleCollision(coObjects);
}



void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		if (level == MARIO_LEVEL_BIG)
		{
			HandleGeneralAnimation(generalAniBigMario, ani);
			if (state == MARIO_STATE_SITDOWN)
			{
				if (nx > 0)
					ani = MARIO_ANI_BIG_SIT_RIGHT;
				else
					ani = MARIO_ANI_BIG_SIT_LEFT;
			}
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			HandleGeneralAnimation(generalAniSmallMario, ani);
		}

		else if (level == MARIO_LEVEL_FIRE)
		{
			HandleGeneralAnimation(generalAniFireMario, ani);
			if (state == MARIO_STATE_SITDOWN)
			{
				if (nx > 0)
					ani = MARIO_ANI_FIRE_SIT_RIGHT;
				else
					ani = MARIO_ANI_FIRE_SIT_LEFT;
			}
			else if (hasAniShootFire == true)
			{
				if (nx > 0)
					ani = MARIO_ANI_FIRE_FIRING_RIGHT;
				else
					ani = MARIO_ANI_FIRE_FIRING_LEFT;
			}
			
			
		}

		else if (level == MARIO_LEVEL_TAIL)
		{
			if (IsStartFlying() || CheckStateFlyingAndFall())
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
			else if (state == MARIO_STATE_SITDOWN)
			{
				if (nx > 0)
					ani = MARIO_ANI_TAIL_SIT_RIGHT;
				else
					ani = MARIO_ANI_TAIL_SIT_LEFT;
			}
			else
			{
				HandleGeneralAnimation(generalAniTailMario, ani);
			}
			if (hasTurnBackTail)
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

		}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	//RenderBoundingBox();
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
		vy = MARIO_GRAVITY - 0.0019999f;
		break;
	case MARIO_STATE_SITDOWN:
		vx = 0;
		break;
	}
}

void CMario::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
	left = x;
	top = y;


	if (level == MARIO_LEVEL_BIG)
	{
		if (state == MARIO_STATE_SITDOWN)
		{
			top = y + 10;
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
		else
		{
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_FIRE)
	{
		if (state == MARIO_STATE_SITDOWN)
		{
			right = x + MARIO_FIRE_BBOX_WIDTH;
			bottom = y + MARIO_FIRE_BBOX_HEIGHT;
		}
		else
		{
			right = x + MARIO_FIRE_BBOX_WIDTH;
			bottom = y + MARIO_FIRE_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_TAIL)
	{
		// update turning tail
		if (hasTurnBackTail)
		{
			//top = y + MARIO_TAIL_BBOX_HEIGHT / 2;
			right = x + MARIO_TAIL_BBOX_WIDTH * 3;
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

// Handle No Collision 
void CMario::HandleNoCollision(vector<LPGAMEOBJECT>* coObjects)
{
		// Intersect logic collision with Koopas
	for (size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CKoopas*>(obj)) {

			double kLeft, kTop, kRight, kBottom, mLeft, mTop, mRight, mBottom;
			obj->GetBoundingBox(kLeft, kTop, kRight, kBottom);
			if (!hasTurnBackTail)
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
		}
		if (dynamic_cast<CFireBall*>(obj) && level == MARIO_LEVEL_FIRE)
		{
			CFireBall* fireball = dynamic_cast<CFireBall*>(obj);

			// fireball was used will set isFiring to false to use again
			if (shootFire == true && fireball->GetIsFiring() == false)
			{
				fireball->SetPosition(this->x, this->y);
				fireball->SetTopBoundary(this->y);
				fireball->SetSpeed(nx * 0.15f, 0.12f);
				fireball->SetIsFiring(true);
				fireball->SetTimeFiringStart();
				shootFire = false;
			}
		}
	}
}

void CMario::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
{
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	if (state != MARIO_STATE_DIE)
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	// No collision occured, proceed normally
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

		if (nx != 0 && ny == 0)
		{
			vx = 0;
			SetState(MARIO_STATE_IDLE);
		}

		// check jump if state is different with mario state fly and fall
		if (ny != 0 && !CheckStateFlyingAndFall())
		{
			vy = 0;
			if (isJumping == true)
			{
				isJumping = false;
			}
		}

		// Check when Mario fall and collide with the ground (all state fly and fall)
		if (ny != 0 && !CheckStateFlyingAndFall())
		{
			isFlying_start = GetTickCount();
			startFlying = false;
			SetIsAbleToFly(false);
		}

		// Check Mario tail and no collision, we set state to FALL 
		/*if (ny != 0 && level == MARIO_LEVEL_TAIL && !CheckStateFlying())
		{
			state = MARIO_STATE_FALL_IDLE;
		}*/


		// Collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			// set state idle when collision, if collision is Coin and ColorBrick - Mario continue flying
			if (CheckStateFlyingAndFall())
			{
				if (!dynamic_cast<CCoin*>(e->obj))
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
								if (level == MARIO_LEVEL_TAIL && hasTurnBackTail)
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
			else if (dynamic_cast<CItem*>(e->obj))
			{
				CItem* item = dynamic_cast<CItem*>(e->obj);
				if (item->GetState() != ITEM_STATE_DISAPPEAR)
				{
					if (level == MARIO_LEVEL_SMALL)
					{
						SetPosition(x, y - 20.0f);
					}
					level++;
					item->SetState(ITEM_STATE_DISAPPEAR);
				}
			}
			else if (dynamic_cast<CQuestion*>(e->obj))
			{
				CQuestion* question = dynamic_cast<CQuestion*>(e->obj);
				if (ny > 0 && nx == 0)
				{
					question->SetState(QUESTION_STATE_BLANK);
				}
			}
			else if (dynamic_cast<CFlower*>(e->obj) || dynamic_cast<CFireFlower*>(e->obj))
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
					SetState(MARIO_STATE_DIE);

			}
			else if (dynamic_cast<CBreakableBrick*>(e->obj))
			{
				CBreakableBrick* bbrick = dynamic_cast<CBreakableBrick*>(e->obj);
				if (nx != 0 && ny == 0 && level == MARIO_LEVEL_TAIL && hasTurnBackTail)
				{
					if (bbrick->GetState() != BREAKBRICK_STATE_BLANK_QUESTION)
					{
						bbrick->SetState(BREAKBRICK_STATE_DISAPPEAR);
					}
				}
				else if (bbrick->GetState() == BREAKBRICK_STATE_COIN)
				{
					bbrick->SetState(BREAKBRICK_STATE_DISAPPEAR);
				}
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
						else if (k->GetState() == KOOPAS_STATE_FLYING)
						{
							k->SetState(KOOPAS_STATE_WALKING);
							k->SetSpeed(-k->vx, k->vy);
							vy = -MARIO_JUMP_DEFLECT_SPEED;
						}
					}
					else if (k->GetState() == KOOPAS_STATE_DIE)
					{
						k->SetState(KOOPAS_STATE_RUNNING_SHELL_RIGHT);
					}

				}
				else if (e->nx != 0 || e->ny > 0)
				{
					if (untouchable == 0)
					{
						if (k->GetState() != KOOPAS_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL && !hasTurnBackTail)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else if (hasTurnBackTail)
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
							else
							{
								flagHolding = true;
								k->SetBeingHolding(true);
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

void CMario::HandleState()
{
	// update acceleration of Mario

	if (state == MARIO_STATE_WALKING_RIGHT || state == MARIO_STATE_WALKING_LEFT || state == MARIO_STATE_HIGH_SPEED_RIGHT
		|| state == MARIO_STATE_HIGH_SPEED_LEFT)
	{

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
			vx += nx * (MARIO_ACCELERATION_SPEED * dt);
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
	if (CheckStateFlyingAndFall())
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
	if (GetTickCount() - turnBackTail_start > 400)
	{
		SetTurnBackTail(false);
	}

	// Check to run high speed for mario
	if (CheckHighSpeedStart() && state != MARIO_STATE_IDLE && !IsStartFlying())
	{
		if (nx > 0)
			SetState(MARIO_STATE_HIGH_SPEED_RIGHT);
		else
			SetState(MARIO_STATE_HIGH_SPEED_LEFT);
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
}

void CMario::SetGeneralAniBigMario(vector<int> &generalAniBigMario)
{
	generalAniBigMario.push_back(MARIO_ANI_BIG_HIGHSPEED_LEFT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_HIGHSPEED_RIGHT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_HOLD_RIGHT_IDLE);
	generalAniBigMario.push_back(MARIO_ANI_BIG_HOLD_LEFT_IDLE);
	generalAniBigMario.push_back(MARIO_ANI_BIG_IDLE_RIGHT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_IDLE_LEFT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_HOLD_RIGHT_WALK);
	generalAniBigMario.push_back(MARIO_ANI_BIG_HOLD_LEFT_WALK);
	generalAniBigMario.push_back(MARIO_ANI_BIG_BRAKING_LEFT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_RUNNING_RIGHT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_WALKING_RIGHT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_BRAKING_RIGHT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_RUNNING_LEFT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_WALKING_LEFT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_JUMPING_RIGHT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_JUMPING_LEFT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_FLY_RIGHT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_FLY_LEFT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_SHOOT_RIGHT);
	generalAniBigMario.push_back(MARIO_ANI_BIG_SHOOT_LEFT);
}

void CMario::SetGeneralAniSmallMario(vector<int>& generalAniSmallMario)
{
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_HIGHSPEED_LEFT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_HIGHSPEED_RIGHT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_HOLD_RIGHT_IDLE);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_HOLD_LEFT_IDLE);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_IDLE_RIGHT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_IDLE_LEFT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_HOLD_RIGHT_WALK);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_HOLD_LEFT_WALK);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_BRAKING_LEFT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_RUNNING_RIGHT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_WALKING_RIGHT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_BRAKING_RIGHT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_RUNNING_LEFT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_WALKING_LEFT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_JUMPING_RIGHT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_JUMPING_LEFT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_FLY_RIGHT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_FLY_LEFT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_SHOOT_RIGHT);
	generalAniSmallMario.push_back(MARIO_ANI_SMALL_SHOOT_LEFT);
}

void CMario::SetGeneralAniFireMario(vector<int> &generalAniFireMario)
{
	generalAniFireMario.push_back(MARIO_ANI_FIRE_HIGHSPEED_LEFT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_HIGHSPEED_RIGHT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_HOLD_RIGHT_IDLE);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_HOLD_LEFT_IDLE);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_IDLE_RIGHT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_IDLE_LEFT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_HOLD_RIGHT_WALK);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_HOLD_LEFT_WALK);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_BRAKING_LEFT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_RUNNING_RIGHT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_WALKING_RIGHT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_BRAKING_RIGHT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_RUNNING_LEFT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_WALKING_LEFT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_JUMPING_RIGHT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_JUMPING_LEFT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_FLY_RIGHT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_FLY_LEFT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_SHOOT_RIGHT);
	generalAniFireMario.push_back(MARIO_ANI_FIRE_SHOOT_LEFT);
}

void CMario::SetGeneralAniTailMario(vector<int>& generalAniTailMario)
{
	generalAniTailMario.push_back(MARIO_ANI_TAIL_HIGHSPEED_LEFT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_HIGHSPEED_RIGHT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_HOLD_RIGHT_IDLE);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_HOLD_LEFT_IDLE);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_IDLE_RIGHT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_IDLE_LEFT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_HOLD_RIGHT_WALK);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_HOLD_LEFT_WALK);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_BRAKING_LEFT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_RUNNING_RIGHT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_WALKING_RIGHT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_BRAKING_RIGHT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_RUNNING_LEFT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_WALKING_LEFT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_JUMPING_RIGHT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_JUMPING_LEFT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_FLYINNG_RIGHT_BOTTOM);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_FLYING_LEFT_BOTTOM);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_SHOOT_RIGHT);
	generalAniTailMario.push_back(MARIO_ANI_TAIL_SHOOT_LEFT);
}


void CMario::HandleGeneralAnimation(vector<int> generalAni, int &ani)
{
		if (state == MARIO_STATE_HIGH_SPEED_LEFT || state == MARIO_STATE_HIGH_SPEED_RIGHT)
		{
			if (state == MARIO_STATE_HIGH_SPEED_LEFT)
			{
				ani = generalAni.at(INDEX_ANI_HIGH_SPEED_LEFT);
			}
			else
			{
				ani = generalAni.at(INDEX_ANI_HIGH_SPEED_RIGHT);
			}
		}
		else
		{
	
			// Set animation braking when vx is oppsite with nx
			if (nx > 0)
			{
				if (vx < 0)
				{
					ani = generalAni.at(INDEX_ANI_BRAKE_LEFT);
				}
				else
				{
					if (isRunning)
					{
						ani = generalAni.at(INDEX_ANI_RUNNING_RIGHT);
					}
					else
					{
						ani = generalAni.at(INDEX_ANI_WALKING_RIGHT);
					}
				}
			}
			else {
				if (vx > 0)
				{
					ani = generalAni.at(INDEX_ANI_BRAKE_RIGHT);
				}
				else
				{
					if (isRunning)
					{
						//DebugOut(L"is running");
						ani = generalAni.at(INDEX_ANI_RUNNING_LEFT);
					}
					else
					{
						ani = generalAni.at(INDEX_ANI_WALKING_LEFT);
					}
				}
			}
	
		}
	
		if (isJumping == true && !CheckStateFlyingAndFall())
		{
			if (state != MARIO_STATE_HIGH_SPEED_LEFT && state != MARIO_STATE_HIGH_SPEED_RIGHT)
			{
				if (nx > 0)
				{
					ani = generalAni.at(INDEX_ANI_JUMPING_RIGHT);;
				}
				else
				{
					ani = generalAni.at(INDEX_ANI_JUMPING_LEFT);;
				}
			}
			else
			{
				if (nx > 0)
				{
					ani = generalAni.at(INDEX_ANI_FLYING_RIGHT);
				}
				else
				{
					ani = generalAni.at(INDEX_ANI_FLYINNG_LEFT);
				}
			}
		}
		if (shoot == -1)
		{
			ani = generalAni.at(INDEX_ANI_SHOOT_RIGHT);
			if (!checkTimeShoot)
			{
				timeShoot_start = GetTickCount();
				checkTimeShoot = true;
			}
			else
			{
				if (GetTickCount() - timeShoot_start > 200)
				{
					checkTimeShoot = false;
					shoot = 0;
				}
			}

		}
		else if (shoot == 1)
		{
			ani = generalAni.at(INDEX_ANI_SHOOT_LEFT);
			if (!checkTimeShoot)
			{
				timeShoot_start = GetTickCount();
				checkTimeShoot = true;
			}

			else
			{
				if (GetTickCount() - timeShoot_start > 200)
				{
					checkTimeShoot = false;
					shoot = 0;
				}
			}
		}
		if (vx == 0)
		{
			if (flagHolding == true && !isJumping)
			{
				if (nx > 0)
				{
					ani = generalAni.at(INDEX_ANI_HOLD_RIGHT_IDLE);
				}
				else ani = generalAni.at(INDEX_ANI_HOLD_LEFT_IDLE);
			}
			else if (flagHolding != true && !isJumping)
			{
				if (nx > 0) ani = generalAni.at(INDEX_ANI_IDLE_RIGHT);
				else ani = generalAni.at(INDEX_ANI_IDLE_LEFT);
			}
		}

		// Set holding for mario
		else if (flagHolding == true)
		{
			if (vx > 0)
			{
				ani = generalAni.at(INDEX_ANI_HOLD_RIGHT_WALK);
			}
			else if (vx < 0)
			{
				ani = generalAni.at(INDEX_ANI_HOLD_LEFT_WALK);
			}

		}
}




void CMario::SetIsJumping(bool value)
{
	isJumping = value;
}

bool CMario::CheckStateFlying()
{
	return (state == MARIO_STATE_FLYING_LEFT || state == MARIO_STATE_FLYING_RIGHT || state == MARIO_STATE_FLYING_IDLE);
}

bool CMario::CheckStateFall()
{
	return (state == MARIO_STATE_FALL_IDLE || state == MARIO_STATE_FALL_LEFT || state == MARIO_STATE_FALL_RIGHT);
}

bool CMario::CheckStateFlyingAndFall()
{
	return (state == MARIO_STATE_FLYING_LEFT || state == MARIO_STATE_FLYING_RIGHT || state == MARIO_STATE_FLYING_IDLE
		|| state == MARIO_STATE_FALL_IDLE || state == MARIO_STATE_FALL_RIGHT || state == MARIO_STATE_FALL_LEFT);
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

