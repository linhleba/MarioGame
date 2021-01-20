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

	if (cx <= minX) cx = minX;
	//if (cx > 2816) cx = 2816;
	if (cx >= maxX) cx = maxX;

	if (basedOnPlayer)
	{
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
			CGame::GetInstance()->SetCamPos(round(posX2), round(posY2));
		}
		else
		{
			CGame::GetInstance()->SetCamPos(round(this->x), round(this->y));
			if (this->x < maxX)
			{
				this->x += 0.06f * dt;
			}
			/*else
			{
				camX = 2064;
			}*/
			if (player->x < this->x)
				player->x = this->x;
			if (player->x > this->x + game->GetScreenWidth())
				player->x = this->x + game->GetScreenWidth();
		}
	}
}
