#include "Koopas.h"
#include "Collision.h"

CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
	
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_DIE)
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	else if (state == KOOPAS_STATE_RUNNING_SHELL_RIGHT || state == KOOPAS_STATE_RUNNING_SHELL_LEFT)
		bottom = y + KOOPAS_BBOX_HEIGHT_SHELL;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (state == KOOPAS_STATE_WALKING)
	{
		if (vx < 0 && x < 100) {
			x = 100; vx = -vx;
		}

		if (vx > 0 && x > 290) {
			x = 290; vx = -vx;
		}
	}
	else if (state == KOOPAS_STATE_RUNNING_SHELL_RIGHT || state == KOOPAS_STATE_RUNNING_SHELL_LEFT)
	{
		if (x < 0) {
			x = 0; vx = -vx;
		}
		DebugOut(L"State:Running shell Koopas \n");
		
		if (coEvents.size() != 0)
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;
			if (nx != 0) vx = -vx;
		}
	}
	if (state == KOOPAS_STATE_DIE)
	{
		if (coEvents.size() != 0)
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		}

	}
	
}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_DIE) {
		ani = KOOPAS_ANI_DIE;
	/*	DWORD timeRenew = GetTickCount();
		if (timeRenew > 1000)
		{
			ani = KOOPAS_ANI_RENEW;
		}*/
	}
	else if (state == KOOPAS_STATE_RUNNING_SHELL_RIGHT || state == KOOPAS_STATE_RUNNING_SHELL_LEFT)
	{
		ani = KOOPAS_ANI_RUNNING_SHELL;
	}
	else if (vx > 0) ani = KOOPAS_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = KOOPAS_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_RUNNING_SHELL_RIGHT:
		//y = 130.0f;
		vx = 0.2f;
		vy = 0;
		break;
	case KOOPAS_STATE_RUNNING_SHELL_LEFT:
		vx = -0.2f;
		vy = 0;
	}

}