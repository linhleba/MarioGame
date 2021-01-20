#include "Camera.h"
#include "Mario.h"
#include "Game.h"
#include "PlayScence.h"

CCamera::CCamera()
{
}

CCamera::CCamera(double x2, double y2, double conY, bool value, double minX, double maxX)
{
	this->posX2 = x2;
	this->posY2 = y2;
	this->conY = conY;
	this->basedOnPlayer = value;
	this->minX = minX;
	this->maxX = maxX;
}

void CCamera::Render()
{
}

void CCamera::GetBoundingBox(double& l, double& t, double& r, double& b)
{
}

void CCamera::Update(DWORD dt)
{
	CGameObject::Update(dt);
	CMario* player = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
	double cx, cy;
	player->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;


	if (basedOnPlayer)
	{
		if (cx <= minX) cx = minX;
		//if (cx > 2816) cx = 2816;
		if (cx >= maxX) cx = maxX;

		if (player->GetIsInSecretRoom())
		{
			CGame::GetInstance()->SetCamPos(round(posX2), round(posY2));
		}
		else
		{
			if (player->GetLevel() != MARIO_LEVEL_TAIL)
			{
				if (cy > conY)
				{
					CGame::GetInstance()->SetCamPos(round(cx), (round)(this->y));
				}
				else
				{
					CGame::GetInstance()->SetCamPos(round(cx), round(cy));
				}
			}
			else
			{
				if (cy > conY)
				{
					CGame::GetInstance()->SetCamPos(round(cx), round(this->y));
				}
				else
				{
					CGame::GetInstance()->SetCamPos(round(cx), round(cy));
				}
			}
		}
	}
	else
	{

		if (player->GetIsInSecretRoom())
		{
			if (cx < posX2)
			{
				cx = posX2;
			}
			if (cx >= 2320)
			{
				cx = 2320;
			}
			if (player->x < posX2)
			{
				player->x = posX2;
			}
			/*if (player->x > 2476)
			{
				player->x = 2476;
			}*/
			CGame::GetInstance()->SetCamPos(round(cx), round(posY2));
		}
		else
		{
			if (cx <= minX) cx = minX;
			//if (cx > 2816) cx = 2816;
			if (cx >= maxX) cx = maxX;
			CGame::GetInstance()->SetCamPos(round(this->x), round(this->y));
			if (this->x < maxX)
			{
				this->x += 0.06f * dt;
			}
			if (player->x < this->x)
				player->x = this->x;
			if (player->x > this->x + game->GetScreenWidth())
				player->x = this->x + game->GetScreenWidth();
		}
	}
}
