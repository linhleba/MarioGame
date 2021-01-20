#include "Koopas.h"
#include "Collision.h"
#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"
#include "PlayScence.h"
#include "Flower.h"
#include "BreakableBrick.h"
#include "IntroScene.h"
#include "ColorBrick.h"
#include "Question.h"
#include "FireFlower.h"

CKoopas::CKoopas(int type)
{
	this->SetIsStaticObject(false);
	typeOfKoopas = type;
	if (type == OBJECT_TYPE_KOOPAS_GREEN_FLYING || type == OBJECT_TYPE_RED_KOOPAS_FLYING)
	{
		SetState(KOOPAS_STATE_FLYING);
	}

	else
	{
		SetState(KOOPAS_STATE_WALKING);
	}
	this->layerRender = 2;

}

void CKoopas::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
	left = x;
	top = y + 2;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_RENEW || state == KOOPAS_STATE_FALL)
	{
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	}
	else if (state == KOOPAS_STATE_RUNNING_SHELL_RIGHT || state == KOOPAS_STATE_RUNNING_SHELL_LEFT)
	{
		if (typeOfKoopas == OBJECT_TYPE_KOOPAS_RED_NORMAL)
		{
			right = x + KOOPAS_BBOX_WIDTH - 6;
			bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
		}
		else
		{
			right = x + KOOPAS_BBOX_WIDTH - 4;
			bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
		}
	}
	else if (state == KOOPAS_STATE_DISAPPEAR || state == KOOPAS_STATE_DIE_FALL)
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
	// state walking
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"vi tri rua la %f \n", y);
	CGameObject::Update(dt, coObjects);
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CMario* redMario = ((CIntroScene*)CGame::GetInstance()->GetCurrentScene())->GetRedMario();
	CMario* greenMario = ((CIntroScene*)CGame::GetInstance()->GetCurrentScene())->GetGreenMario();
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();


	if (state != KOOPAS_STATE_WALKING)
	{
		isAbleFall = true;
	}

	if (state != KOOPAS_STATE_DISAPPEAR)
	{
		vy += 0.0012 * dt;
	}

	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	// Die fall means fall freely, dont have collision
	if (state != KOOPAS_STATE_DIE_FALL)
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 
	// Set is not fall for Koopas Red

	if (state == KOOPAS_STATE_FLYING)
	{
		if (typeOfKoopas == OBJECT_TYPE_KOOPAS_GREEN_FLYING)
		{
			if (!isFLying)
			{
				timeFlying_start = GetTickCount();
				isFLying = true;
			}
			else
			{
				// Set time for Koopas flying
				if (GetTickCount() - timeFlying_start < 100)
				{
					vy = -0.15f;
				}
				// when time is greater than 2000, set isFlying = false to return wal
				if (GetTickCount() - timeFlying_start > 2000)
				{
					isFLying = false;
				}
			}
		}
		else if (typeOfKoopas == OBJECT_TYPE_RED_KOOPAS_FLYING)
		{

			if (!isFlyingUp)
			{
				vy = KOOPAS_RED_FLYING_SPEED;
				if (GetTickCount() - timeFlyingUp_start > 1500)
				{
					isFlyingUp = true;
					timeFlyingUp_start = GetTickCount();

				}
			}
			else
			{
				vy = -KOOPAS_RED_FLYING_SPEED;

				if (GetTickCount() - timeFlyingUp_start > 1500)
				{
					isFlyingUp = false;
					timeFlyingUp_start = GetTickCount();
				}
			}
		}
	}

	else if (state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_DIE_FALL || state == KOOPAS_STATE_FALL)
	{
		// Set GetTickCount when unitialized time_Renew_Start
		if (!isRenewStart)
		{
			timeRenew_start = GetTickCount();
			isRenewStart = true;
		}
		// Set for the Koopas renews if enough time to renew
		else
		{
			if (GetTickCount() - timeRenew_start > 5000)
			{
				if (id == ID_PLAY_SCENE)
				{
					SetState(KOOPAS_STATE_RENEW);
					isRenewStart = false;

					// Set time start walking koopas
					timeWalking_start = GetTickCount();
				}
			}
		}
		// Set status for mario holding koopas
		if (isHeld == true)
		{
			if (id == ID_PLAY_SCENE)
			{
				if (!mario->GetIsHolding())
				{
					isHeld = false;
					mario->SetFlagHolding(false);

					mario->SetShoot(mario->nx);
					SetState(KOOPAS_STATE_RUNNING_SHELL_RIGHT);
					if (mario->GetLevel() == MARIO_LEVEL_SMALL)
					{
						SetPosition(this->x, this->y - 5);
					}
					else
					{
						SetPosition(this->x, this->y);
					}
					SetSpeed(mario->nx * KOOPAS_SPINNING_SPEED, this->vy);
				}
				else
				{
					mario->SetFlagHolding(true);
					/*if (mario->GetLevel() != MARIO_LEVEL_SMALL)
					{
						x = mario->x + 10 * mario->nx;
						y = mario->y + 5;
					}
					else
					{
						x = mario->x + 10 * mario->nx;
						y = mario->y;
					}*/

					UpdatePositionHeld();
					vy = 0;
				}
			}

			else if (id == ID_INTRO_SCENE)
			{
				if (isBeingRedHolding)
				{
					if (!redMario->GetIsHolding())
					{
						//DebugOut(L"rua dang held \n");
						isHeld = false;
						redMario->SetFlagHolding(false);
						redMario->SetShoot(redMario->nx);
						SetState(KOOPAS_STATE_RUNNING_SHELL_RIGHT);
						SetPosition(this->x, this->y);
						SetSpeed(redMario->nx * 0.15f, this->vy);
					}
					else
					{
						redMario->SetFlagHolding(true);
						if (redMario->GetLevel() != MARIO_LEVEL_SMALL)
						{
							x = redMario->x + 20 * redMario->nx;
							y = redMario->y + 5;
						}
						else
						{
							x = redMario->x + 10 * redMario->nx;
							y = redMario->y;
						}
					}
				}
				if (isBeingGreenHolding)
				{
					if (!greenMario->GetIsHolding())
					{
						isHeld = false;
						greenMario->SetFlagHolding(false);
						greenMario->SetShoot(greenMario->nx);
						SetState(KOOPAS_STATE_RUNNING_SHELL_RIGHT);
						SetPosition(this->x, this->y);
						SetSpeed(greenMario->nx * 0.14f, this->vy);
					}
					else
					{
						greenMario->SetFlagHolding(true);
						if (greenMario->GetLevel() != MARIO_LEVEL_SMALL)
						{
							x = greenMario->x + 10 * greenMario->nx;
							y = greenMario->y + 5;
						}
						else
						{
							x = greenMario->x + 10 * greenMario->nx;
							y = greenMario->y;
						}
					}
				}
				vy = 0;
			}
		}
	}
	else if (state == KOOPAS_STATE_RENEW)
	{
		if (GetTickCount() - timeWalking_start > 2000)
		{
			SetState(KOOPAS_STATE_WALKING);

			// set the position again when Koopas renew (if not the pos will be wrong)
			SetPosition(this->x, this->y - (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE));
			SetSpeed(this->vx * mario->nx, vy);
			isHeld = false;
			mario->SetFlagHolding(false);
		}
		// Set status for mario holding koopas
		if (isHeld == true)
		{
			if (!mario->GetIsHolding())
			{
				isHeld = false;
				mario->SetFlagHolding(false);
				mario->SetShoot(mario->nx);
				SetState(KOOPAS_STATE_RUNNING_SHELL_RIGHT);
				SetPosition(this->x, this->y);
				SetSpeed(mario->nx * 0.25f, this->vy);
			}

			UpdatePositionHeld();
			vy = 0;
		}
	}


	if (x < 0 && vx < 0) {
		x = 0; vx = -vx;
	}

	// Handle coliision with Koopas

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (isAbleFall == false && state == KOOPAS_STATE_WALKING && typeOfKoopas == OBJECT_TYPE_KOOPAS_RED_NORMAL)
		{
			if (y - prePositionOnGround >= 1.0f)
			{
				y -= 5;
				if (vx < 0)
				{
					x += 12;
				}
				else
				{
					x -= 12;
				}
				vx = -vx;
				//isAbleFall = true;
			}
		}
	}
	else
	{
		double min_tx, min_ty, nx = 0, ny;
		double rdx = 0;
		double rdy = 0;

		collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];

			// HANDLE COLLISION IN INTRO SCENE
			if (!dynamic_cast<CMario*>(e->obj) && nx == 0)
			{
				prePositionOnGround = y;
				isAbleFall = false;
			}

			// Change the direction if collision nx
			if (nx != 0)
			{

				nx = -nx;
				vx = -vx;
				vy = 0;
			}

			// when it touches the ground, vy will equal to 0
			if (this->ny != 0 && nx == 0) vy = 0;

			if (id == INDEX_OF_MAP_1_SCENE)
			{
				if (dynamic_cast<CQuestion*>(e->obj))
				{
					CQuestion* question = dynamic_cast<CQuestion*>(e->obj);
					if (state == KOOPAS_STATE_RUNNING_SHELL_LEFT || state == KOOPAS_STATE_RUNNING_SHELL_RIGHT)
					{
						question->SetState(QUESTION_STATE_BLANK);
					}
				}
			}

			// Xet dieu kien trong intro scene
			if (id == ID_INTRO_SCENE)
			{
				if (ny != 0 && state == KOOPAS_STATE_DIE)
				{
					vx = 0;
				}

				if (dynamic_cast<CMario*>(e->obj))
				{
					CMario* mario = dynamic_cast<CMario*>(e->obj);
					if (state == KOOPAS_STATE_DIE && e->ny != 0)
					{
						mario->SetState(MARIO_STATE_BEING_HITTED);
						vx = -0.1f;
						vy = -0.1f;
					}
					if (mario->GetIsHolding())
					{
						mario->SetFlagHolding(true);
						SetBeingHolding(true);
					}
				}
			}

			// Xu li rua spinning
			if (state == KOOPAS_STATE_RUNNING_SHELL_LEFT || state == KOOPAS_STATE_RUNNING_SHELL_RIGHT)
			{
				if (dynamic_cast<CGoomba*>(e->obj))
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
					goomba->SetState(GOOMBA_STATE_DIE);
					goomba->SetGoombaDie();
					goomba->SetTickCount();
				}
				else if (dynamic_cast<CKoopas*>(e->obj))
				{
					if (nx > 0) dieFallDirection = 1;
					else if (nx < 0) dieFallDirection = -1;
					e->obj->SetState(KOOPAS_STATE_DIE_FALL);
					//this->SetState(KOOPAS_STATE_DIE_FALL);
				}
				else if (dynamic_cast<CFlower*>(e->obj))
				{
					CFlower* flower = dynamic_cast<CFlower*>(e->obj);
					flower->SetState(FLOWER_STATE_DIE);
				}
				else if (dynamic_cast<CBreakableBrick*>(e->obj))
				{
					if (ny == 0 && nx != 0)
					{
						CBreakableBrick* bbrick = dynamic_cast<CBreakableBrick*>(e->obj);
						bbrick->SetState(BREAKBRICK_STATE_DISAPPEAR);
					}
				}
			}

		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING_LEFT;
	if (state != KOOPAS_STATE_DISAPPEAR)
	{
		if (typeOfKoopas == OBJECT_TYPE_KOOPAS_GREEN_FLYING || typeOfKoopas == OBJECT_TYPE_KOOPAS_GREEN_NORMAL
			|| typeOfKoopas == OBJECT_TYPE_KOOPAS_FINAL || typeOfKoopas == OBJECT_TYPE_KOOPAS_FASTER)
		{
			if (state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_DIE_FALL || state == KOOPAS_STATE_FALL) {
				if (isFaceUp)
				{
					ani = KOOPAS_ANI_DIE_FACING_UP;
				}
				else
				{
					ani = KOOPAS_ANI_DIE;
				}
			}
			else if (state == KOOPAS_STATE_RUNNING_SHELL_RIGHT || state == KOOPAS_STATE_RUNNING_SHELL_LEFT)
			{
				if (isFaceUp)
				{
					ani = KOOPAS_ANI_RUNNING_SHELL_FACING_UP;
				}
				else
				{
					ani = KOOPAS_ANI_RUNNING_SHELL;
				}
			}
			else if (state == KOOPAS_STATE_RENEW)
			{
				if (isFaceUp)
				{
					ani = KOOPAS_ANI_RENEW_FACING_UP;
				}
				else
				{
					ani = KOOPAS_ANI_RENEW;
				}
			}
			else if (state == KOOPAS_STATE_FLYING)
			{
				ani = KOOPAS_ANI_FLYING;
			}
			else if (vx > 0) ani = KOOPAS_ANI_WALKING_RIGHT;
			else if (vx <= 0) ani = KOOPAS_ANI_WALKING_LEFT;
		}
		else if (typeOfKoopas == OBJECT_TYPE_KOOPAS_RED_NORMAL || typeOfKoopas == OBJECT_TYPE_RED_KOOPAS_FLYING)
		{
			if (state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_DIE_FALL || state == KOOPAS_STATE_FALL) {
				if (isFaceUp)
				{
					ani = KOOPAS_RED_ANI_DIE_FACING_UP;
				}
				else
				{
					ani = KOOPAS_RED_ANI_DIE;
				}
			}
			else if (state == KOOPAS_STATE_RUNNING_SHELL_RIGHT || state == KOOPAS_STATE_RUNNING_SHELL_LEFT)
			{
				if (isFaceUp)
				{
					ani = KOOPAS_RED_ANI_RUNNING_SHELL_FACING_UP;
				}
				else
				{
					ani = KOOPAS_RED_ANI_RUNNING_SHELL;
				}
			}
			else if (state == KOOPAS_STATE_RENEW)
			{
				if (isFaceUp)
				{
					ani = KOOPAS_RED_ANI_RENEW_FACING_UP;
				}
				else
				{
					ani = KOOPAS_RED_ANI_RENEW;
				}
			}
			else if (state == KOOPAS_STATE_FLYING)
			{
				ani = KOOPAS_RED_ANI_FLYING;
			}
			else if (vx > 0) ani = KOOPAS_RED_ANI_WALKING_RIGHT;
			else if (vx <= 0) ani = KOOPAS_RED_ANI_WALKING_LEFT;
		}
		else if (typeOfKoopas == OBJECT_TYPE_KOOPAS_BLACK)
		{
			if (state == KOOPAS_STATE_DIE)
			{
				ani = KOOPAS_BLACK_ANI_DIE_FACEDOWN;
			}
			else if (state == KOOPAS_STATE_DIE_FALL)
			{
				ani = KOOPAS_BLACK_ANI_DIE_FACEDOWN;
			}
		}
		animation_set->at(ani)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CKoopas::Reset()
{
	//DebugOut(L"state hien tai la %d \n", this->GetState());
	if (this->GetState() != KOOPAS_STATE_DIE_FALL)
	{
		this->x = this->originX;
		this->y = this->originY;
		switch (typeOfKoopas)
		{
		case OBJECT_TYPE_KOOPAS_RED_NORMAL:
			SetState(KOOPAS_STATE_WALKING);
			break;
		case OBJECT_TYPE_KOOPAS_GREEN_NORMAL:
			SetState(KOOPAS_STATE_WALKING);
			break;
		case OBJECT_TYPE_KOOPAS_GREEN_FLYING:
			SetState(KOOPAS_STATE_FLYING);
			break;
		}
	}
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		//y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE - 1;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		isFaceUp = false;
		vx = KOOPAS_WALKING_SPEED;
		//vy = 0.1f;
		break;
	case KOOPAS_STATE_RUNNING_SHELL_RIGHT:
		//y = 130.0f;
		vx = KOOPAS_SPINNING_SPEED;
		vy = 0;
		break;
	case KOOPAS_STATE_RUNNING_SHELL_LEFT:
		vx = -KOOPAS_SPINNING_SPEED;
		vy = 0;
		break;
	case KOOPAS_STATE_DIE_FALL:
		vy = -0.2f;
		vx = 0.1f;
		break;
	case KOOPAS_STATE_FLYING:
		if (typeOfKoopas == OBJECT_TYPE_KOOPAS_GREEN_FLYING)
			vx = -KOOPAS_WALKING_SPEED;
		else if (typeOfKoopas == OBJECT_TYPE_RED_KOOPAS_FLYING)
			vx = 0;
		break;
	case KOOPAS_STATE_DISAPPEAR:
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_FALL:
		vy = -KOOPAS_FALL_SPEED_Y;
		vx = nx * KOOPAS_FALL_SPEED_X;
		break;
	}

}

void CKoopas::UpdatePositionHeld()
{
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (mario->GetLevel())
	{
	case MARIO_LEVEL_SMALL:
		x = mario->x + 10 * mario->nx;
		y = mario->y;
		break;
	case MARIO_LEVEL_TAIL:
		if (mario->nx > 0)
		{
			x = mario->x + 17 * mario->nx;
			y = mario->y + 5;
		}
		else
		{
			x = mario->x + 11 * mario->nx;
			y = mario->y + 5;
		}
		break;
	default:
		x = mario->x + 10 * mario->nx;
		y = mario->y + 5;
		break;
	}
}
