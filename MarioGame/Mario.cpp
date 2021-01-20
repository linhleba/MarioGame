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
#include "Score.h"
#include "PlayScence.h"
#include "Tail.h"
#include "Pipe.h"
#include "MovingBrick.h"
#include "Boomerang.h"
#include "BoomerangMan.h"

CMario::CMario(double x, double y) : CGameObject()
{
	typeOfMario = OBJECT_TYPE_MARIO_RED;
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	SetGeneralAniBigMario(generalAniBigMario);
	SetGeneralAniSmallMario(generalAniSmallMario);
	SetGeneralAniFireMario(generalAniFireMario);
	SetGeneralAniTailMario(generalAniTailMario);
	SetGeneralAniGreenMario(generalAniGreenMario);

	//Set ani green mario


	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	this->layerRender = 99;
}

CMario::CMario(int type, double x, double y)
{
	typeOfMario = type;
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	SetGeneralAniBigMario(generalAniBigMario);
	SetGeneralAniSmallMario(generalAniSmallMario);
	SetGeneralAniFireMario(generalAniFireMario);
	SetGeneralAniTailMario(generalAniTailMario);
	SetGeneralAniGreenMario(generalAniGreenMario);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	DebugOut(L"vi tri x la %f \n", this->x);
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	prePositionY = this->y;
	// check if transform is true
	if (isTransforming)
	{
		if (checkTransformStart == false)
		{
			checkTransformStart = true;
			transform_start = GetTickCount();
		}
		else
		{
			if (GetTickCount() - transform_start > TIME_OF_MARIO_TRANSFORMING)
			{
				checkTransformStart = false;
				isTransforming = false;
			}
		}
	}
	else
	{
		CGameObject::Update(dt);
		// Cal stack 
		if (isFirstTimeHighSpeed || CheckStateFlying())
		{
			SetIsTimeStackUp(true);
			SetTheStackUp();
		}
		else
		{
			SetTheStackDown();
		}
		// Simple fall down
		int id = CGame::GetInstance()->GetCurrentScene()->GetId();
		if (id == ID_INTRO_SCENE && state == MARIO_STATE_FALL_IDLE)
		{
			vx = -0.09f;
		}

		if (state != MARIO_STATE_PIPE_STANDING)
		{
			if (CheckStateFall() && level == MARIO_LEVEL_TAIL)
			{
				vy += MARIO_GRAVITY_FALLING_SPEED * dt;
			}
			else
			{
			/*	if (isOnMovingBrick)
				{

				}*/

				if (!isOnMovingBrick)
				{
					vy += MARIO_GRAVITY * dt;
				}
				else
				{
					if (this->vy < 0)
					{
						vy += MARIO_GRAVITY_JUMPING * dt;
					}
					else if (this->vy >= 0)
					{
						if (isJumping)
						{
							vy += MARIO_GRAVITY * dt;
						}
						else
						{
							vy += MOVING_BRICK_GRAVITY_SPEED * dt;
						}
					}
				}
			}
		}

		HandleNoCollision(coObjects);

		// Add left collision
		if (vx < 0 && x < 0) x = 0;

		// Add current right collision
		if (vx > 0 && x > 2806) x = 2806;

		HandleState();
		HandleCollision(coObjects);

		// Handle fireball for FIRE MARIO
		if (hasAniShootFire)
		{
			if (!isEnableFireBall)
			{
				isEnableFireBall_start = GetTickCount();
				isEnableFireBall = true;
			}
			else
			{
				if (GetTickCount() - isEnableFireBall_start > 150)
				{
					isEnableFireBall = false;
					hasAniShootFire = false;
				}
			}
		}

		// Simple handle for end game, switch scene
		if (isEndGame == true)
		{
			SetState(MARIO_STATE_WALKING_RIGHT);
			if (GetTickCount() - endGame_start > 3000)
			{
				CGame::GetInstance()->SwitchScene(INDEX_OF_WORLD_MAP_SCENE);
			}
		}

		if (state == MARIO_STATE_PIPE_STANDING)
		{
			if (secondUppingPipe)
			{
				vy = -0.01f;
				if (GetTickCount() - secondInPipe_start > 2000)
				{
					SetState(MARIO_STATE_IDLE);
					lockControl = false;
					secondUppingPipe = false;
					isUppingPipe = false;
					currentPipeIndex = -1;
				}
			}

			else
			{
				if (isFallDowningPipe)
				{
					SetState(MARIO_STATE_IDLE);
					lockControl = false;
					currentPipeIndex = -1;
					isFallDowningPipe = false;
				}
				else
				{
					lockControl = true;
					if (isDowningPipe || isDownUpPipe)
					{
						if (!checkTimeInDowingPipe)
						{
							checkTimeInDowingPipe = true;
							timeInDowingPipe_start = GetTickCount();
						}

						else
						{
							if (isDowningPipe)
							{
								if (GetTickCount() - timeInDowingPipe_start > 2000)
								{
									checkTimeInDowingPipe = false;
									isReadyToPiping = true;
								}
							}
							else if (isDownUpPipe)
							{
								if (GetTickCount() - timeInDowingPipe_start > 2000)
								{
									isReadyToPiping = true;
									SetState(MARIO_STATE_PIPE_STANDING);
									secondUppingPipe = true;
									secondInPipe_start = GetTickCount();
									isUppingPipe = false;
								}
							}
						}
					}

					else if (isUppingPipe)
					{
						vy = -0.01f;
						vx = 0;
						if (!checkTimeInUppingPipe)
						{
							checkTimeInUppingPipe = true;
							timeInUppingPipe_start = GetTickCount();
						}
						else
						{
							if (GetTickCount() - timeInUppingPipe_start > 1700)
							{
								isReadyToPiping = true;
								SetState(MARIO_STATE_PIPE_STANDING);
								secondUppingPipe = true;
								secondInPipe_start = GetTickCount();
							}

						}
					}
				}
			}
		}

		// set position for the Mario die
		if (y > 1200)
		{
			CGame::GetInstance()->SetLifeDown();
			CGame::GetInstance()->SwitchScene(INDEX_OF_WORLD_MAP_SCENE);
		}
	}
}



void CMario::Render()
{
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();
	int ani = -1;
	if (isAppeared)
	{
		if (typeOfMario == OBJECT_TYPE_MARIO_RED)
		{
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
					if (state == MARIO_STATE_BEING_HITTED)
					{
						ani = MARIO_RED_ANI_KOOPAS_HIT;
					}
					if (state == MARIO_STATE_LOOKING_AHEAD)
					{
						ani = MARIO_RED_ANI_LEFT_LOOK_AHEAD;
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
		}
		else if (typeOfMario == OBJECT_TYPE_MARIO_GREEN)
		{
			HandleGeneralAnimation(generalAniGreenMario, ani);
			//animation_set->at(MARIO_ANI_BIG_BRAKING_LEFT)->Render(x, y, 255);
		}

		// Handle for transforming for play scene
		if (id != INDEX_OF_INTRO_SCENE)
		{
			if (isTransforming)
			{
				if (level == MARIO_LEVEL_SMALL)
				{
					if (nx > 0)
					{
						ani = MARIO_ANI_BIG_RIGHT_TRANSFORMING;
					}
					else
					{
						ani = MARIO_ANI_BIG_LEFT_TRANSFORMING;
					}
				}
				if (level == MARIO_LEVEL_TAIL)
				{
					if (nx > 0)
					{
						ani = MARIO_ANI_TAIL_RIGHT_TRANSFORMING;
					}
					else
					{
						ani = MARIO_ANI_TAIL_LEFT_TRANSFORMING;
					}
				}
				if (level == MARIO_LEVEL_BIG)
				{
					if (isLevelUp)
					{
						if (nx > 0)
						{
							ani = MARIO_ANI_BIG_RIGHT_TRANSFORMING;
						}
						else
						{
							ani = MARIO_ANI_BIG_LEFT_TRANSFORMING;
						}
					}
					else
					{
						if (nx > 0)
						{
							ani = MARIO_ANI_TAIL_RIGHT_TRANSFORMING;
						}
						else
						{
							ani = MARIO_ANI_TAIL_LEFT_TRANSFORMING;
						}
					}
				}
			}
		}
		else
		{
			if (isTransforming)
			{
				if (level == MARIO_LEVEL_TAIL)
				{
					ani = INTRO_MARIO_ANI_TAIL_LEFT_TRANSFORMING;
				}
				else if (level == MARIO_LEVEL_SMALL)
				{
					ani = INTRO_MARIO_ANI_BIG_RIGHT_TRANSFORMING;
				}
			}
		}

		int alpha = 255;
		if (untouchable) alpha = 128;

		animation_set->at(ani)->Render(round(x), round(y), alpha);
	}
	//RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
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
		vy = MARIO_FALLING_SPEED_Y;
		break;
	case MARIO_STATE_SITDOWN:
		vx = 0;
		break;
	case MARIO_STATE_PIPE_STANDING:
		vy = 0.01f;
		break;
	}
}

void CMario::SetTheStackUp()
{
	if (isTimeStackUp == true)
	{
		if (GetTickCount() - timeStackUp_start > 400 && levelOfStack < 7)
		{
			levelOfStack++;
			isTimeStackUp = false;
		}
	}
}

void CMario::SetTheStackDown()
{
	if (GetTickCount() - timeStackUp_start > 200 && levelOfStack > 0)
	{
		timeStackUp_start = GetTickCount();
		levelOfStack--;
		isTimeStackUp = false;
	}
}

void CMario::SetIsTimeStackUp(bool value)
{
	if (isTimeStackUp == false)
	{
		isTimeStackUp = value;
		timeStackUp_start = GetTickCount();
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
		//if (hasTurnBackTail)
		//{
		//	//top = y + MARIO_TAIL_BBOX_HEIGHT / 2;
		//	right = x + MARIO_TAIL_BBOX_WIDTH * 3;
		//	bottom = y + MARIO_TAIL_BBOX_HEIGHT;
		//}
		if (nx > 0)
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

		// Set state when has Tail
		if (level == MARIO_LEVEL_TAIL && firstTailing && dynamic_cast<CTail*>(obj))
		{
			StartTurningBack();
			firstTailing = false;
			CTail* tail = dynamic_cast<CTail*>(obj);
			tail->SetState(TAIL_STATE_MOVING);
			tail->SetPosition(x + MARIO_TAIL_BBOX_WIDTH / 2, y + MARIO_TAIL_BBOX_HEIGHT - 5);
			//tail->nx = nx;
		}

	}
}

void CMario::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
{
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();
	if (state != MARIO_STATE_DIE && state != MARIO_STATE_PIPE_STANDING && id != INDEX_OF_WORLD_MAP_SCENE)
	{
		if (coObjects != NULL)
		{
			collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
		}
	}
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
		CScore* score = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetScore();
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

			// Handle collsion when pipe downing or upping
			if (dynamic_cast<CPipe*>(e->obj))
			{
				CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
				if (pipe->GetTypeOfPipe() == OBJECT_TYPE_PIPE_DOWNING)
				{
					isDowningPipe = true;
					currentPipeIndex = pipe->GetIdPipe();
				}
				else
				{
					isDowningPipe = false;
				}

				if (pipe->GetTypeOfPipe() == OBJECT_TYPE_PIPE_UPPING)
				{
					isUppingPipe = true;
					currentPipeIndex = pipe->GetIdPipe();
				}
				else
				{
					isUppingPipe = false;
				}

				if (pipe->GetTypeOfPipe() == OBJECT_TYPE_DOWN_UP_PIPE)
				{
					isDownUpPipe = true;
					currentPipeIndex = pipe->GetIdPipe();
				}
				else
				{
					isDownUpPipe = false;
				}
			}
			else
			{
				isDowningPipe = false;
				isUppingPipe = false;
			}

			// Handle Collision for IntroScene 
			if (dynamic_cast<CMario*>(e->obj))
			{
				CMario* mario = dynamic_cast<CMario*>(e->obj);
				if (e->ny != 0)
				{
					if (this->typeOfMario == OBJECT_TYPE_MARIO_GREEN && mario->typeOfMario == OBJECT_TYPE_MARIO_RED)
					{
						// with in this state, red will stop walking
						mario->SetState(MARIO_STATE_SITDOWN);
						isRedAbleWalk = false;
						this->SetState(MARIO_STATE_JUMP_HIGH_SPEED);
					}
				}
			}

			// Handle collsion into the special cards in the final background
			if (dynamic_cast<CCard*>(e->obj))
			{
				//vector<int> cards = CGame::GetInstance()->GetCards();
				CCard* card = dynamic_cast<CCard*>(e->obj);
				switch (card->GetState())
				{
				case CARD_STATE_FIRE_FLOWER:
					CGame::GetInstance()->PushCards(HUD_TYPE_FIREFLOWER_CARD_ANI);
					card->SetState(CARD_STATE_FIRE_FLOWER_MOVING);
					card_id = HUD_TYPE_FIREFLOWER_CARD_ANI;
					break;
				case CARD_STATE_MUSHROOM:
					CGame::GetInstance()->PushCards(HUD_TYPE_MUSHROOM_CARD_ANI);
					card->SetState(CARD_STATE_MUSHROOM_MOVING);
					card_id = HUD_TYPE_MUSHROOM_CARD_ANI;
					break;
				case CARD_STATE_STAR:
					CGame::GetInstance()->PushCards(HUD_TYPE_STAR_CARD_ANI);
					card->SetState(CARD_STATE_STAR_MOVING);
					card_id = HUD_TYPE_STAR_CARD_ANI;
					break;
				}
				lockControl = true;
				isEndGame = true;
				endGame_start = GetTickCount();
			}
			if (dynamic_cast<CBoomerang*>(e->obj))
			{
				CBoomerang* boomerang = dynamic_cast<CBoomerang*>(e->obj);

				if (untouchable == 0)
				{
					if (level > MARIO_LEVEL_SMALL)
					{
						isTransforming = true;
						level--;
						isLevelUp = false;
						StartUntouchable();
					}
					else
					{
						SetState(MARIO_STATE_DIE);
					}
				}
			}
			if (dynamic_cast<CBoomerangMan*>(e->obj))
			{
				CBoomerangMan* boomerangMan = dynamic_cast<CBoomerangMan*>(e->obj);
				if (e->ny < 0)
				{
					score->SetScore(1, e->obj->x, e->obj->y);
					boomerangMan->SetState(BOOMERANG_MAN_STATE_DIE);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (level > MARIO_LEVEL_SMALL)
						{
							// Update mario tail and turning tail won't die
							if (level == MARIO_LEVEL_TAIL && hasTurnBackTail)
							{
								score->SetScore(1, e->obj->x, e->obj->y);
								boomerangMan->SetState(BOOMERANG_MAN_STATE_DIE);
							}
							else
							{
								isTransforming = true;
								level--;
								isLevelUp = false;
								StartUntouchable();
							}

						}
						else
						{
							SetState(MARIO_STATE_DIE);
						}
					}
				}
			}

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					//levelOfScored = 1;
					score->SetScore(1, e->obj->x, e->obj->y);
					if (goomba->GetState() == GOOMBA_STATE_WALKING)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						goomba->SetGoombaDie();
						goomba->SetTickCount();

						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}

					else if (goomba->GetState() == GOOMBA_STATE_FLYING)
					{
						goomba->SetState(GOOMBA_STATE_WALKING);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() == GOOMBA_STATE_WALKING || goomba->GetState() == GOOMBA_STATE_FLYING)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								// Update mario tail and turning tail won't die
								if (level == MARIO_LEVEL_TAIL && hasTurnBackTail)
								{
									score->SetScore(1, e->obj->x, e->obj->y);
									goomba->SetState(GOOMBA_STATE_DIE);
									goomba->SetGoombaDie();
									goomba->SetTickCount();
								}

								else
								{
									isTransforming = true;
									level--;
									isLevelUp = false;
									StartUntouchable();
								}

							}
							else
							{
								SetState(MARIO_STATE_DIE);
							}
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CCoin*>(e->obj))
			{
				score->SetScore(1, e->obj->x, e->obj->y);
				CGame::GetInstance()->SetMoney();
				CCoin* coin = dynamic_cast<CCoin*>(e->obj);
				coin->SetState(COIN_STATE_DISAPPEAR);

			}
			else if (dynamic_cast<CItem*>(e->obj))
			{
				CItem* item = dynamic_cast<CItem*>(e->obj);
				if (item->GetState() != ITEM_STATE_DISAPPEAR)
				{
					if (item->GetTypeOfItem() != OBJECT_TYPE_GREEN_MUSHROOM)
					{
						if (level == MARIO_LEVEL_SMALL)
						{
							SetPosition(x, y - 20.0f);
						}
						if (level != MARIO_LEVEL_TAIL && level != MARIO_LEVEL_FIRE)
						{
							isTransforming = true;
							isLevelUp = true;
							level++;
							SetPosition(x, y - 10.0f);
							score->SetScore(1, e->obj->x, e->obj->y);
						}
						else
						{
							score->SetScore(10, e->obj->x, e->obj->y);
						}
					}
					else
					{

						score->SetScore(0, x, y);
						CGame::GetInstance()->SetLifeUp();
					}
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
				if (untouchable == 0)
				{
					if (level > MARIO_LEVEL_SMALL)
					{
						isTransforming = true;
						if (id != INDEX_OF_INTRO_SCENE)
						{
							level--;
						}
						else
						{
							level = MARIO_LEVEL_SMALL;
						}
						isLevelUp = false;
						StartUntouchable();
					}
					else
						SetState(MARIO_STATE_DIE);
				}
			}
			else if (dynamic_cast<CBreakableBrick*>(e->obj))
			{
				CBreakableBrick* bbrick = dynamic_cast<CBreakableBrick*>(e->obj);
				/*if (nx != 0 && ny == 0 && level == MARIO_LEVEL_TAIL && hasTurnBackTail)
				{
					if (bbrick->GetState() != BREAKBRICK_STATE_BLANK_QUESTION)
					{
						bbrick->SetState(BREAKBRICK_STATE_DISAPPEAR);
					}
				}*/
				if (bbrick->GetState() == BREAKBRICK_STATE_COIN)
				{
					CGame::GetInstance()->SetMoney();
					bbrick->SetState(BREAKBRICK_STATE_DISAPPEAR);
				}

				if (e->ny > 0)
				{
					if (bbrick->GetState() == BREAKBRICK_STATE_APPEAR)
					{
						bbrick->SetState(BREAKBRICK_STATE_MOVING_UP);
					}
				}
			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}

			else if (dynamic_cast<CMovingBrick*> (e->obj))
			{
			
				isOnMovingBrick = true;
				/*x += min_tx * dx - nx * 0.7f;
				y += min_ty * dy - ny * 0.7f;*/
				CMovingBrick* movingBrick = dynamic_cast<CMovingBrick*>(e->obj);
				if (e->ny <= 0)
				{
					movingBrick->SetState(MOVING_BRICK_STATE_FALLING);
					vy = movingBrick->vy;
				}
				if (e->nx != 0)
				{
					vx = 0;
				}
			}
			// Check Koopas
			else if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* k = dynamic_cast<CKoopas*>(e->obj);
				if (e->ny < 0)
				{
					score->SetScore(1, e->obj->x, e->obj->y);
					//DebugOut(L"dang va cham ny < 0 \n");

					if (k->GetState() == KOOPAS_STATE_DIE || k->GetState() == KOOPAS_STATE_RENEW)
					{
						//DebugOut(L"koopas dang running \n");
						k->SetState(KOOPAS_STATE_RUNNING_SHELL_RIGHT);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					else if (k->GetState() == KOOPAS_STATE_RUNNING_SHELL_RIGHT || k->GetState() == KOOPAS_STATE_RUNNING_SHELL_LEFT)
					{
						k->SetState(KOOPAS_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					else
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

				}
				else if (e->nx != 0)
				{
					// Playscene when Koopas fall on the head of Mario will be different from with Intro Scene
					if (untouchable == 0)
					{
						if (k->GetState() != KOOPAS_STATE_DIE && k->GetState() != KOOPAS_STATE_DIE_FALL && k->GetState()
							!= KOOPAS_STATE_RENEW)
						{
							if (level > MARIO_LEVEL_SMALL && !hasTurnBackTail)
							{
								isTransforming = true;
								if (id != INDEX_OF_INTRO_SCENE)
								{
									level--;
								}
								else
								{
									level = MARIO_LEVEL_SMALL;
								}
								isLevelUp = false;
								StartUntouchable();
							}
							else if (hasTurnBackTail)
							{
								score->SetScore(1, e->obj->x, e->obj->y);
								k->SetState(KOOPAS_STATE_DIE);
								k->SetIsFaceUp(true);
							}
							else
							{
								SetState(MARIO_STATE_DIE);
							}
						}
						else if (k->GetState() == KOOPAS_STATE_DIE || k->GetState() == KOOPAS_STATE_RENEW ||
							k->GetState() == KOOPAS_STATE_DIE_FALL)
						{
							// shoot but not hold
							if (isHolding != true)
							{
								if (nx < 0)
								{
									shoot = 1;
									k->SetState(KOOPAS_STATE_RUNNING_SHELL_RIGHT);
								}
								else
								{
									shoot = -1;
									k->SetState(KOOPAS_STATE_RUNNING_SHELL_LEFT);
								}
							}
							else
							{
								//flagHolding = true;
								k->SetBeingHolding(true);
							}

						}
					}
				}
			}

			if (!dynamic_cast<CMovingBrick*>(e->obj))
			{
				isOnMovingBrick = false;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::HandleState()
{
	// update acceleration of Mario
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();


	if (id == INDEX_OF_MAP_1_SCENE)
	{
		if (state == MARIO_STATE_DIE)
		{
			if (!isTimeDie)
			{
				isTimeDie = true;
				timeDie_start = GetTickCount();
				lockControl = true;
			}
			else
			{
				if (GetTickCount() - timeDie_start > 1000)
				{
					CGame::GetInstance()->SetLifeDown();
					CGame::GetInstance()->SwitchScene(ID_WORLD_MAP_SCENE);
					lockControl = false;
					isTimeDie = false;
					return;
				}
			}
		}

	}

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
		SetTheStackDown();
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
		if (id == ID_PLAY_SCENE || id == INDEX_OF_BASE_SCENE)
		{
			if (state == MARIO_STATE_FLYING_RIGHT || state == MARIO_STATE_FALL_RIGHT)
			{
				vx = MARIO_FLYING_SPEED;
				SetTheStackUp();
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

void CMario::SetGeneralAniBigMario(vector<int>& generalAniBigMario)
{
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_HIGHSPEED_LEFT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_HIGHSPEED_RIGHT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_HOLD_RIGHT_IDLE);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_HOLD_LEFT_IDLE);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_IDLE_RIGHT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_IDLE_LEFT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_HOLD_RIGHT_WALK);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_HOLD_LEFT_WALK);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_BRAKING_LEFT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_RUNNING_RIGHT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_WALKING_RIGHT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_BRAKING_RIGHT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_RUNNING_LEFT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_WALKING_LEFT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_JUMPING_RIGHT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_JUMPING_LEFT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_FLY_RIGHT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_FLY_LEFT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_SHOOT_RIGHT);
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_SHOOT_LEFT);
	// Define standing when collision pipe (20)
	generalAniBigMario.emplace_back(MARIO_ANI_BIG_PIPE_STANDING);
}

void CMario::SetGeneralAniSmallMario(vector<int>& generalAniSmallMario)
{
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_HIGHSPEED_LEFT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_HIGHSPEED_RIGHT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_HOLD_RIGHT_IDLE);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_HOLD_LEFT_IDLE);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_IDLE_RIGHT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_IDLE_LEFT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_HOLD_RIGHT_WALK);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_HOLD_LEFT_WALK);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_BRAKING_LEFT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_RUNNING_RIGHT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_WALKING_RIGHT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_BRAKING_RIGHT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_RUNNING_LEFT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_WALKING_LEFT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_JUMPING_RIGHT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_JUMPING_LEFT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_FLY_RIGHT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_FLY_LEFT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_SHOOT_RIGHT);
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_SHOOT_LEFT);
	// Define standing when collision pipe (20)
	generalAniSmallMario.emplace_back(MARIO_ANI_SMALL_PIPE_STANDING);
}

void CMario::SetGeneralAniFireMario(vector<int>& generalAniFireMario)
{
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_HIGHSPEED_LEFT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_HIGHSPEED_RIGHT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_HOLD_RIGHT_IDLE);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_HOLD_LEFT_IDLE);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_IDLE_RIGHT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_IDLE_LEFT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_HOLD_RIGHT_WALK);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_HOLD_LEFT_WALK);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_BRAKING_LEFT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_RUNNING_RIGHT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_WALKING_RIGHT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_BRAKING_RIGHT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_RUNNING_LEFT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_WALKING_LEFT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_JUMPING_RIGHT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_JUMPING_LEFT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_FLY_RIGHT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_FLY_LEFT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_SHOOT_RIGHT);
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_SHOOT_LEFT);
	// Define standing when collision pipe (20)
	generalAniFireMario.emplace_back(MARIO_ANI_FIRE_PIPE_STANDING);
}

void CMario::SetGeneralAniTailMario(vector<int>& generalAniTailMario)
{
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_HIGHSPEED_LEFT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_HIGHSPEED_RIGHT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_HOLD_RIGHT_IDLE);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_HOLD_LEFT_IDLE);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_IDLE_RIGHT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_IDLE_LEFT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_HOLD_RIGHT_WALK);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_HOLD_LEFT_WALK);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_BRAKING_LEFT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_RUNNING_RIGHT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_WALKING_RIGHT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_BRAKING_RIGHT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_RUNNING_LEFT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_WALKING_LEFT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_JUMPING_RIGHT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_JUMPING_LEFT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_FLYINNG_RIGHT_BOTTOM);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_FLYING_LEFT_BOTTOM);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_SHOOT_RIGHT);
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_SHOOT_LEFT);
	// Define standing when collision pipe (20)
	generalAniTailMario.emplace_back(MARIO_ANI_TAIL_PIPE_STANDING);
}

void CMario::SetGeneralAniGreenMario(vector<int>& generalAniGreenMario)
{
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_RUNNING_LEFT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_RUNNING_RIGHT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_HOLDING_IDLE_RIGHT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_HOLDING_IDLE_LEFT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_IDLE_RIGHT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_IDLE_LEFT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_WALKING_RIGHT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_WALKING_LEFT);
	// brake left
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_IDLE_LEFT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_RUNNING_RIGHT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_WALKING_RIGHT);
	// brake right
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_IDLE_RIGHT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_RUNNING_LEFT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_WALKING_LEFT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_JUMPING_RIGHT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_JUMPING_LEFT);
	// flying right and left
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_JUMP_FALL_RIGHT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_JUMP_FALL_LEFT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_KICKING_RIGHT);
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_KICKING_LEFT);
	// Define standing when collision pipe (20)
	generalAniGreenMario.emplace_back(MARIO_GREEN_ANI_BIG_IDLE_LEFT);
}


void CMario::HandleGeneralAnimation(vector<int> generalAni, int& ani)
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
	if (shoot == 1)
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
	else if (shoot == -1)
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
		if (flagHolding != true && !isJumping)
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

	if (state == MARIO_STATE_PIPE_STANDING)
	{
		ani = generalAni.at(INDEX_ANI_PIPE_STANDING);
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

