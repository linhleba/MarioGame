#include "HUD.h"
#include "Mario.h"
#include "PlayScence.h"
#include "Utils.h"


CHUD::CHUD(int type)
{
	typeOfHUD = type;
}

void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int id = CGame::GetInstance()->GetCurrentScene()->GetId();

	double camCurrentX = CGame::GetInstance()->GetCamX();
	double camCurrentY = CGame::GetInstance()->GetCamY();

	double camPreX = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetCamPreX();
	double camPreY = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetCamPreY();

	if (id == INDEX_OF_PLAY_SCENE)
	{
		x += camCurrentX - camPreX;
		y += camCurrentY - camPreY;
	}

}

void CHUD::Render()
{
	int ani = -1;
	switch (typeOfHUD)
	{
	case OBJECT_TYPE_HUD_PANEL:
		ani = HUD_TYPE_PANEL_ANI;
		break;
	case OBJECT_TYPE_HUD_WORLD:
		ani = HUD_TYPE_WORLD_ANI;
		break;
	case OBJECT_TYPE_HUD_MARIO_LUIGI:
		ani = HUD_TYPE_MARIO_LUIGI_ANI;
		break;
	case OBJECT_TYPE_HUD_LIFE:
		ani = HUD_TYPE_NUMBER_ZERO_ANI;
		break;
	case OBJECT_TYPE_HUD_TIME_PICKER:
		ani = HUD_TYPE_NUMBER_ZERO_ANI;
		break;
	case OBJECT_TYPE_HUD_SCORE:
		ani = HUD_TYPE_NUMBER_ZERO_ANI;
		break;
	case OBJECT_TYPE_HUD_MONEY:
		ani = HUD_TYPE_NUMBER_ZERO_ANI;
		break;
	case OBJECT_TYPE_HUD_STACK_NORMAL:
		ani = HUD_TYPE_STACK_NORMAL_EMPTY_ANI;
		break;
	case OBJECT_TYPE_HUD_STACK_MAX:
		ani = HUD_TYPE_STACK_MAX_EMPTY_ANI;
		break;
	case OBJECT_TYPE_HUD_BLACK:
		ani = HUD_TYPE_BLACK_ANI;
		break;
	default:
		break;
	}
	if (ani != -1)
	{
		animation_set->at(ani)->Render(x, y);
	}
}

void CHUD::Render(int indexTime)
{
	int ani = -1;

	scoreCounter = CGame::GetInstance()->GetScore();
	moneyCounter = CGame::GetInstance()->GetMoney();

	scoreCounters.clear();
	moneyCounters.clear();

	int id = CGame::GetInstance()->GetCurrentScene()->GetId();
	if (id == INDEX_OF_PLAY_SCENE)
	{
		CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		levelOfStack = mario->GetLevelOfStack();
	}


	while (scoreCounter > 0)
	{
		scoreCounters.push_back(scoreCounter % 10);
		scoreCounter /= 10;
	}

	if (scoreCounter == 0)
	{
		while (scoreCounters.size() < 7)
		{
			scoreCounters.push_back(0);
		}
	}

	// set tens position and digits position for money for rendering
	moneyCounters.push_back(moneyCounter / 10);
	moneyCounters.push_back(moneyCounter % 10);
	if (moneyCounters.at(0) > 0)
	{
		isAbleTensPos = true;
	}
	switch (typeOfHUD)
	{
	case OBJECT_TYPE_HUD_TIME_PICKER:
		ani = indexTime;
		break;
	case OBJECT_TYPE_HUD_SCORE:
		ani = scoreCounters.at(indexTime);
		break;
	case OBJECT_TYPE_HUD_MONEY:
		if (isAbleTensPos)
		{
			ani = moneyCounters.at(indexTime);
		}
		else
		{
			if (indexTime == 1)
			{
				ani = moneyCounters.at(indexTime);
			}
		}
		break;
	case OBJECT_TYPE_HUD_STACK_NORMAL:
		if ((indexTime + 1) > levelOfStack)
		{
			ani = HUD_TYPE_STACK_NORMAL_EMPTY_ANI;
		}
		else
		{
			ani = HUD_TYPE_STACK_NORMAL_FILLED_ANI;
		}
		break;
	case OBJECT_TYPE_HUD_STACK_MAX:
		if (levelOfStack == 7)
		{
			ani = HUD_TYPE_STACK_MAX_FILLED_ANI;
		}
		else
		{
			ani = HUD_TYPE_STACK_MAX_EMPTY_ANI;
		}
		break;
	default:
		return;
	}
	if (ani != -1)
	{
		animation_set->at(ani)->Render(x, y);
	}
}

void CHUD::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
}

void CHUD::SetState(int state)
{
}
